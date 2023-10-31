#include <iostream>
#include <typeinfo>
#include <memory>
#include <stdexcept>
#include <string>

class Any {
public:
    template <typename T>
    Any(T value) : data(new Holder<T>(value)) {}

    template <typename T>
    T get() const {
        if (typeid(T) != data->typeInfo()) {
            throw std::runtime_error("Type mismatch");
        }
        return static_cast<Holder<T>*>(data.get())->value;
    }

private:
    struct HolderBase {
        virtual const std::type_info& typeInfo() const = 0;
        virtual ~HolderBase() {}
    };

    template <typename T>
    struct Holder : public HolderBase {
        Holder(T value) : value(value) {}

        const std::type_info& typeInfo() const override {
            return typeid(T);
        }

        T value;
    };

    std::unique_ptr<HolderBase> data;
};

int main() {
    Any a(5);
    std::cout << a.get<int>() << std::endl; // 5
    Any b(std::string("strrr"));
    std::cout << b.get<std::string>()<< std::endl;

    try {
        std::cout << a.get<std::string>() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}