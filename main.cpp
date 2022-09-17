//
//  main.cpp
//  graph
//
//  Created by Никита on 09.08.2022.
//



#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

vector < vector < int >>
read_graph (const string & name_file, vector < pair < int, int >>&list_edges,
        vector < int >&counter)
{
  ifstream fin;
  fin.open (name_file);
  vector < vector < int >>graph;
  int apex, edges;
  vector < pair < int, int >>pairs;
  list_edges.clear ();
  counter.clear ();
  if (fin.is_open ())
    {
      fin >> apex >> edges;
      vector < int >v (apex, 0);
      graph.resize (apex, v);
      auto zero = make_pair (0, 0);
      pairs.resize (graph.size (), zero);
      for (int k = 0; k < edges; k++)
    {
      int start, end;
      fin >> start >> end;
      auto p1 = make_pair (start, end);
      list_edges.push_back (p1);
      graph[start][end] = 1;
      graph[end][start] = 1;
      pairs[start].first += 1;
      pairs[end].first += 1;
      pairs[start].second = start;
      pairs[end].second = end;
    }
    }
  else
    {
      cout << "file not read" << endl;
    }
  sort (pairs.begin (), pairs.end ());
  for (int i = pairs.size () - 1; i >= 0; i--)
    {
      counter.push_back (pairs[i].second);
    }
  return graph;
}

vector < int >
decide (vector < vector < int >>&graph, const vector < int >&counter)
{
  vector < int >vColors (graph.size (), -1);
for (auto it:counter)
    {
      int i = it;
      vector < bool > colored (graph.size (), false);
      for (int j = 0; j < graph.size (); j++)
    {
      if (graph[i][j] == 1)
        {
          if (vColors[j] > -1)
        {
          colored[vColors[j]] = true;
        }
        }
    }
      for (int k = 0; k < graph.size (); k++)
    {
      if (!colored[k])
        {
          vColors[i] = k;
          break;
        }
    }
    }
  return vColors;
}

int
main ()
{

  string path = "/Users/nikpav/Desktop/с ++/graph/data";
  auto it = fs::directory_iterator (path);
  vector < fs::path > array_path;
  copy_if (fs::begin (it), fs::end (it), std::back_inserter (array_path),
       [](const auto & entry)
       {
       return fs::is_regular_file (entry);}
  );

for (auto & p:array_path)
    {
      vector < int >counter;
      vector < pair < int, int >>edges;
      vector < vector < int >>graph =
    read_graph (p.string (), edges, counter);
      vector < int >colored2 = decide (graph, counter);
      int max = -1;
      for (int i = 0; i < colored2.size (); i++)
    {
      if (colored2[i] > max)
        {
          max = colored2[i];
        }
    }
      cout << p.string () << " " << max + 1 << endl;
      cout << endl;
    for (auto i:edges)
    {
      if (colored2[i.first] == colored2[i.second])
        {
          cout << "Error, colored test: " << p.string () << endl;
          cout << i.first << " " << i.second << endl;
          break;
        }
    }
    }
  return 0;
}
