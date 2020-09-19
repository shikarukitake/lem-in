#!/usr/bin/env python3

import networkx as nx
import sys
import os
import matplotlib.pyplot as plt

def select_size(len_nodes):
    if (len_nodes <= 30):
        return (10, 10)
    elif (len_nodes <= 100):
        return (20, 20)
    elif (len_nodes <= 300):
        return (30, 30)
    elif (len_nodes <= 500):
        return (40, 40)    
    elif (len_nodes <= 1000):
        return (80, 80)
    elif (len_nodes > 1000):
        return (100, 100)

def add_edge(f_item, s_item, graph=None):
    graph.add_edge(f_item, s_item)
    graph.add_edge(s_item, f_item)


def parse_room(line, nodes):
    line = line.split(" ")
    if len(line) != 3:
        raise ValueError
    if len(line[0]) > 5:
        line[0] = line[0][:5]
    nodes[line[0]] = (int(line[1]), int(line[2]))


def parse_edge(line, edges):
    line = line.split("-")
    if len(line) != 2:
        raise ValueError
    line[1] = line[1].rstrip("\n")
    edges.append((line[0], line[1]))


def parse(name, nodes, edges):

    with open(name, 'r') as f:
        for line in f:
            if line[0] == "#":
                pass
            elif ' ' in line:
                parse_room(line, nodes)
            elif '-' in line:
                parse_edge(line, edges)
            else:
                pass

if __name__ == "__main__":
    if len(sys.argv) == 2:
        try:
            name = sys.argv[1] + ".png"
            nodes = dict()
            edges = list()
            parse(sys.argv[1], nodes, edges)
            graph = nx.Graph()
            graph.add_nodes_from(nodes)
            graph.add_edges_from(edges)
            figsize = select_size(len(nodes.keys()))
            plt.figure(3, figsize=figsize)
            nx.draw(graph, with_labels=True)
            plt.savefig(name)
            plt.close()
            print("Done. Graph in " + name + " file")
            os.system("open " + name)
        except Exception as e:
            print("Something wrong...")
    else:
        print("Usage: ./graph.py map_file")