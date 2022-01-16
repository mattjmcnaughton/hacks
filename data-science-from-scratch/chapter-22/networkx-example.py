import networkx as nx


if __name__ == "__main__":
    G = nx.Graph()

    G.add_node(1)
    G.add_nodes_from([2, 3])
    G.add_nodes_from([
        (4, {"color": "red"})
    ])

    G.add_edge(1, 2)
    G.add_edges_from([(2, 3), (1, 3)])

    print(G.nodes)

