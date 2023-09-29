# Dijkstra's Shortest Path Algorithm in C++

This C++ program calculates the shortest path between two nodes in a graph using Dijkstra's algorithm. It reads graph data from a file named `graf.txt` where each line represents a connection between nodes along with their respective weights.

## Usage

1. **Graph Data File (`graf.txt`):** Create a text file named `graf.txt` containing graph data in the format: `node1 node2 weight`.

    Example:
    ```
    1 2 5
    1 3 3
    2 4 6
    3 4 2
    ```

2. **Run the Program:** Open and run the `main.cpp` file in your IDE.

3. **Menu Options:**
   - **1:** Load graph data from `graf.txt`.
   - **2:** Run Dijkstra's algorithm to find the shortest path.
   - **3:** Display the shortest path between specified nodes.
   - **4:** Exit the program.

## Example

Suppose `graf.txt` contains the following data:

```
1 2 5
1 3 3
2 4 6
3 4 2
```

1. Select option **1** to load graph data.
2. Select option **2** to run the algorithm.
3. Select option **3** and enter start node `1` and end node `4` to see the shortest path.
