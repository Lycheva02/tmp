#include <algorithm>

template<typename T>
class TBasePtr {
protected:
    TBasePtr() = default;
    T* p = nullptr;
public:
    TBasePtr(T* from = nullptr) : p(from) { }

    T* operator->() const {
        return p;
    }

    T& operator*() const {
        return *p;
    }

    friend bool operator != (const TBasePtr& left, const TBasePtr& right) {
      return left.p != right.p;
    }

    friend bool operator == (const TBasePtr& left, const TBasePtr& right) {
      return left.p == right.p;
    }

    operator bool() const {
        return p != nullptr;
    }
};

template<typename T>
class TIntrusivePtr : public TBasePtr<T> {
public:
    TIntrusivePtr(T* from) : TBasePtr<T>(from) {
        if (this->p) {
            this->p->Inc();
        }
    }

    TIntrusivePtr(const TIntrusivePtr& other) : TIntrusivePtr<T>(other.p) { }

    TIntrusivePtr(TIntrusivePtr&& other) noexcept : TIntrusivePtr<T>(other.p) {
            other.Release();
    }

    TIntrusivePtr& operator=(TIntrusivePtr other) {
        std::swap(this->p, other.p);
        return *this;
    }

    ~TIntrusivePtr() {
        if (this->p) {
            this->p->Dec();
            if (this->p->RefCount() == 0) {
                delete this->p;
            }
        }
    }

    size_t UseCount() const {
        if (this->p) {
            return this->p->RefCount();
        } else {
            return 0;
        }
    }

    T* Get() const {
        return this->p;
    }

    void Reset(TIntrusivePtr<T> other = nullptr) {
        std::swap(this->p, other.p);
    }

    T* Release() {
        T* ans = this->p;
        if (ans) {
            ans->Dec();
        }
        this->p = nullptr;
        return ans;
    }

    size_t RefCount() const {
        return UseCount();
    }
};



template <typename T>
class TRefCounter
{
public:
    TRefCounter() = default;

    size_t RefCount() {
        return ref_count;
    }

private:
    friend TIntrusivePtr<T>;

    size_t Dec() {
        --ref_count;
        return ref_count;
    }

    size_t Inc() {
        ++ref_count;
        return ref_count;
    }
    size_t ref_count = 0;
};

template <typename T, typename... Args>
TIntrusivePtr<T> MakeIntrusive(Args&&... params) {
    return TIntrusivePtr<T>(new T(std::forward<Args>(params)...));
};