import sys

def read_graph(file_path):
    edges = set()
    with open(file_path, 'r') as file:
        for line in file:
            vertices = line.strip().split('\t')[:2]
            weight = line.strip().split('\t')[2]
            edge = tuple(sorted(vertices) + [weight])
            edges.add(edge)
    return edges

def compare_graphs(file1, file2):
    graph1 = read_graph(file1)
    graph2 = read_graph(file2)

    if graph1 == graph2:
        print("Графы идентичны.")
    else:
        print("Графы различаются.")

input_file = sys.argv[1]
output_file = sys.argv[2]

compare_graphs(input_file, output_file)