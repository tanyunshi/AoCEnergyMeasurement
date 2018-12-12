#!/usr/bin/env python3

from collections import deque


def sum_metadata(numbers):
    if not numbers:
        return 0

    nb_child = numbers.popleft()
    nb_meta = numbers.popleft()
    children = [sum_metadata(numbers) for _i in range(nb_child)]
    meta_data = [numbers.popleft() for _j in range(nb_meta)]

    return sum(meta_data + children)


class Node:
    def __init__(self, numbers):
        self.nb_child = numbers.popleft()
        self.nb_meta = numbers.popleft()
        self.children = [Node(numbers) for _i in range(self.nb_child)]
        self.meta_data = [numbers.popleft() for _j in range(self.nb_meta)]

    def get_sum_meta(self):
        if not self.children:
            return sum(self.meta_data)

        total = 0
        for meta in self.meta_data:
            try:
                total += self.children[meta-1].get_sum_meta()
            except IndexError:
                pass
        return total


if __name__ == "__main__":
    with open('data', 'r') as infile:
        numbers = [int(number) for number in infile.read().split()]
        result = sum_metadata(deque(numbers))
        print('Solution 1 :', result)
        print('Solution 2 :', Node(deque(numbers)).get_sum_meta())
