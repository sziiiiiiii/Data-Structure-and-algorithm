# 定义一个函数，使用Prim算法找到最小生成树
def prim_mst(graph):
    V = len(graph) # 图中顶点的数量

    parent = [None] * V # 存储最小生成树的父节点
    key = [float('inf')] * V # 存储顶点的键值
    mst_set = [False] * V # 标记顶点是否被包含在最小生成树中

    key[0] = 0 # 从第一个顶点开始构建最小生成树
    parent[0] = -1 # 第一个顶点没有父节点

    # 构建V-1条边，每次选择一个顶点加入最小生成树
    for count in range(V-1):
        u = min_key(key, mst_set) # 找到键值最小的顶点
        mst_set[u] = True # 将顶点标记为已被包含在最小生成树中

        # 更新与选定顶点相邻的未被包含在最小生成树中的顶点的键值和父节点
        for v in range(V):
            # 如果顶点v与u相邻，并且顶点v未被包含在最小生成树中，并且边的权值小于v的键值
            if graph[u][v] and not mst_set[v] and graph[u][v] < key[v]:
                parent[v] = u # 更新顶点v的父节点为u
                key[v] = graph[u][v] # 更新顶点v的键值为边的权值

    # 打印最小生成树的边和权值
    print("Edge \tWeight")
    for i in range(1, V):
        print(parent[i], "-", i, "\t", graph[i][parent[i]])

# 定义一个函数，找到最小键值的顶点
def min_key(key, mst_set):
    min_value = float('inf')
    min_index = -1

    for v in range(len(key)):
        # 如果顶点的键值小于当前最小值，并且顶点未被包含在最小生成树中
        if key[v] < min_value and not mst_set[v]:
            min_value = key[v]
            min_index = v

    return min_index

# 测试代码
graph = [[0, 2, 0, 6, 0],
         [2, 0, 3, 8, 5],
         [0, 3, 0, 0, 7],
         [6, 8, 0, 0, 9],
         [0, 5, 7, 9, 0]]

prim_mst(graph)
