using System;
using System.Collections.Generic;
using System.Linq;

namespace scc
{
	public class Edge
	{
		public int Source, Target;
		public Edge(int s, int t)
		{
			Source = s;
			Target = t;
		}
	}
	class MainClass
	{
		public static void Main(String[] args)
		{
			int[] tokens = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
			int n = tokens[0], m = tokens[1];

			Graph g = new Graph(n);

			for (int i = 0; i < m; ++i)
			{
				int[] t = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
				g.AddEdge(t[0], t[1]);
			}

			List<List<int>> sccs = Search(g);

			Console.Error.WriteLine("Done with sccs! - " + sccs.Count);
			for (int i = 0; i < sccs.Count; ++i)
			{
				Console.Write(sccs[i].Count + " ");
				for (int j = 0; j < sccs[i].Count; ++j)
				{
					Console.Write(sccs[i][j] + " ");
				}
				Console.WriteLine();
			}
		}

		public static List<List<int>> Search(Graph graph)
		{
			var stronglyConnectedComponents = new List<List<int>>();

			int preCount = 0;
			var low = new int[graph.VertexCount];
			var visited = new bool[graph.VertexCount];
			var stack = new Stack<int>();

			var minStack = new Stack<int>();
			var enumeratorStack = new Stack<IEnumerator<int>>();
			var enumerator = Enumerable.Range(0, graph.VertexCount).GetEnumerator();
			int h = 0;
			while (true)
			{
				if ((++h) % 100000 == 0 )
				{
					Console.Error.WriteLine(h);
					if (enumerator.MoveNext()) Console.Error.WriteLine("-> " + enumerator.Current);
				}
				if (enumerator.MoveNext())
				{
					
					int v = enumerator.Current;
					//Console.WriteLine(v);
					if (!visited[v])
					{

						low[v] = preCount++;
						visited[v] = true;
						stack.Push(v);
						int min = low[v];
						// Level down

						minStack.Push(min);
						enumeratorStack.Push(enumerator);
						enumerator = Enumerable.Range(0, graph.OutgoingEdgeCount(v))
							.Select(i => graph.OutgoingEdge(v, i).Target)
							.GetEnumerator();
					}
					else if (minStack.Count > 0)
					{
						int min = minStack.Pop();
						if (low[v] < min) min = low[v];
						minStack.Push(min);
					}
				}
				else
				{

					// Level up
					if (enumeratorStack.Count == 0) break;

					enumerator = enumeratorStack.Pop();
					int v = enumerator.Current;
					int min = minStack.Pop();

					if (min < low[v])
					{
						low[v] = min;
					}
					else
					{
						List<int> component = new List<int>();

						int w;
						do
						{
							w = stack.Pop();
							component.Add(w);
							low[w] = graph.VertexCount;
						} while (w != v);
						stronglyConnectedComponents.Add(component);
					}

					if (minStack.Count > 0)
					{
						min = minStack.Pop();
						if (low[v] < min) min = low[v];
						minStack.Push(min);
					}
				}
			}
			return stronglyConnectedComponents;
		}

		public class Graph
		{
			public int VertexCount = 0;

			public List<Edge>[] adjlist;

			public int OutgoingEdgeCount(int v)
			{
				return adjlist[v].Count;
			}

			public Edge OutgoingEdge(int from, int index)
			{
				return adjlist[from][index];
			}

			public Graph(int n)
			{
				VertexCount = n;
				adjlist = new List<Edge>[n];
			}


			public void AddEdge(int from, int to)
			{
				if (adjlist[from] == null)
				{
					adjlist[from] = new List<Edge>();
				}
				adjlist[from].Add(new Edge(from, to));
			}

		}
	}
}
