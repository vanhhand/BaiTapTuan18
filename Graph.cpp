#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
using namespace std;

// Lớp biểu diễn một đỉnh trong đồ thị
class Vertex
{
public:
    string name; // Tên của đỉnh

    Vertex(string name) : name(name) {}
};

// Cấu trúc biểu diễn một cạnh giữa hai đỉnh
struct Edge
{
    int length = 0; // Độ dài mặc định là 0
};

// Lớp biểu diễn đồ thị
class Graph
{
    static const int MAX = 5; // Số đỉnh tối đa
    vector<Vertex> vertexList; // Danh sách đỉnh
    Edge edgeMatrix[MAX][MAX]; // Ma trận cạnh

public:
    // Hàm khởi tạo
    Graph()
    {
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                edgeMatrix[i][j].length = 0;
    }

    // Thêm đỉnh mới
    void AddNode(Vertex v)
    {
        if (vertexList.size() < MAX)
        {
            vertexList.push_back(v);
        }
        else
        {
            cout << "Không thể thêm đỉnh mới. Giới hạn tối đa (" << MAX << ") đã đạt.\n";
        }
    }

    // Xóa một đỉnh theo tên
    void RemoveNode(string name)
    {
        int index = GetVertexIndex(name);
        if (index == -1)
        {
            cout << "Không tìm thấy đỉnh để xóa.\n";
            return;
        }

        // Xóa đỉnh khỏi danh sách đỉnh
        vertexList.erase(vertexList.begin() + index);

        // Xóa các cạnh liên quan trong ma trận cạnh
        for (int i = 0; i < MAX; i++)
        {
            edgeMatrix[index][i].length = 0;
            edgeMatrix[i][index].length = 0;
        }

        cout << "Đỉnh " << name << " đã được xóa.\n";
    }

    // Thêm cạnh giữa hai đỉnh
    void AddEdge(string name1, string name2, int length)
    {
        int index1 = GetVertexIndex(name1);
        int index2 = GetVertexIndex(name2);

        if (index1 == -1 || index2 == -1)
        {
            cout << "Không tìm thấy một hoặc cả hai đỉnh.\n";
            return;
        }

        edgeMatrix[index1][index2].length = length;
        edgeMatrix[index2][index1].length = length; // Đồ thị vô hướng
    }

    // Xóa cạnh giữa hai đỉnh
    void RemoveEdge(string name1, string name2)
    {
        int index1 = GetVertexIndex(name1);
        int index2 = GetVertexIndex(name2);

        if (index1 == -1 || index2 == -1)
        {
            cout << "Không tìm thấy một hoặc cả hai đỉnh.\n";
            return;
        }

        edgeMatrix[index1][index2].length = 0;
        edgeMatrix[index2][index1].length = 0;
        cout << "Cạnh giữa " << name1 << " và " << name2 << " đã được xóa.\n";
    }

    // Tìm chỉ số của một đỉnh theo tên
    int GetVertexIndex(string name)
    {
        for (int i = 0; i < vertexList.size(); i++)
        {
            if (vertexList[i].name == name)
                return i;
        }
        return -1;
    }

    // Duyệt đồ thị theo chiều sâu (DFS)
    void DFS(string startName)
    {
        int startIndex = GetVertexIndex(startName);
        if (startIndex == -1)
        {
            cout << "Không tìm thấy đỉnh bắt đầu.\n";
            return;
        }

        vector<bool> visited(vertexList.size(), false);
        stack<int> s;
        s.push(startIndex);

        cout << "Thứ tự duyệt DFS: ";
        while (!s.empty())
        {
            int current = s.top();
            s.pop();

            if (!visited[current])
            {
                cout << vertexList[current].name << " ";
                visited[current] = true;

                for (int i = vertexList.size() - 1; i >= 0; i--)
                {
                    if (edgeMatrix[current][i].length > 0 && !visited[i])
                    {
                        s.push(i);
                    }
                }
            }
        }
        cout << endl;
    }

    // Duyệt đồ thị theo chiều rộng (BFS)
    void BFS(string startName)
    {
        int startIndex = GetVertexIndex(startName);
        if (startIndex == -1)
        {
            cout << "Không tìm thấy đỉnh bắt đầu.\n";
            return;
        }

        vector<bool> visited(vertexList.size(), false);
        queue<int> q;
        q.push(startIndex);
        visited[startIndex] = true;

        cout << "Thứ tự duyệt BFS: ";
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            cout << vertexList[current].name << " ";

            for (int i = 0; i < vertexList.size(); i++)
            {
                if (edgeMatrix[current][i].length > 0 && !visited[i])
                {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    // In danh sách đỉnh
    void PrintVertexList()
    {
        cout << "Danh sách đỉnh:\n";
        for (const auto &v : vertexList)
        {
            cout << v.name << " ";
        }
        cout << endl;
    }

    // In toàn bộ ma trận cạnh
    void PrintAllEdges()
    {
        cout << "Ma trận cạnh:\n";
        for (int i = 0; i < vertexList.size(); i++)
        {
            for (int j = 0; j < vertexList.size(); j++)
            {
                cout << edgeMatrix[i][j].length << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph bandoVN;

    // Thêm đỉnh
    bandoVN.AddNode(Vertex("Hanoi"));
    bandoVN.AddNode(Vertex("Hai Duong"));
    bandoVN.AddNode(Vertex("Hai Phong"));
    bandoVN.AddNode(Vertex("Nam Dinh"));
    bandoVN.AddNode(Vertex("Thai Binh"));

    // Thêm cạnh
    bandoVN.AddEdge("Hanoi", "Hai Duong", 50);
    bandoVN.AddEdge("Hanoi", "Hai Phong", 100);
    bandoVN.AddEdge("Hai Duong", "Nam Dinh", 60);
    bandoVN.AddEdge("Nam Dinh", "Thai Binh", 70);

    // In danh sách đỉnh và ma trận cạnh
    bandoVN.PrintVertexList();
    bandoVN.PrintAllEdges();

    // Duyệt theo chiều sâu
    bandoVN.DFS("Hanoi");

    // Duyệt theo chiều rộng
    bandoVN.BFS("Hanoi");

    // Xóa đỉnh
    bandoVN.RemoveNode("Nam Dinh");

    // Xóa cạnh
    bandoVN.RemoveEdge("Hanoi", "Hai Phong");

    // In lại danh sách đỉnh và ma trận cạnh
    bandoVN.PrintVertexList();
    bandoVN.PrintAllEdges();

    return 0;
}
