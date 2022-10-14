#include "dfs.hpp"

void recurse_dfs(knn_graph &graph, const int curr, const int target, std::vector<int> &par,
        std::vector<double> &walked_increment, double &walked, bool &found)
{
    if(curr == target || found) {
        found = true;
        return;
    }

    walked += walked_increment[curr];

    for(auto &[next, weight]: graph.edges[curr]) {
        if(par[next] == -1) {
            par[next] = curr;
            walked_increment[next] = weight;

            recurse_dfs(graph, next, target, par, walked_increment, walked, found);
        }
    }
}

std::pair<std::vector<int>, double> search::dfs(knn_graph &graph, int st, int target)
{
    int n = graph.vertices.size();
    bool found = false;
    std::vector<int> par(n, -1);
    std::vector<double> walked_increment(n, 0.0);

    double walked = 0.0;
    par[st] = st;

    recurse_dfs(graph, st, target, par, walked_increment, walked, found);

    std::vector<int> path;

    int curr = target;
    path.push_back(target);

    while(curr != st) {
        path.push_back(par[curr]);
        curr = par[curr];
    }

    std::reverse(path.begin(), path.end());

    return std::make_pair(path, walked);
}
