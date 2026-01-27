template <typename T>
class SegTree
{
public:
      struct Node
      {
      public:
            T value;
      };

      int Size;
      Node Default;
      vector<Node> tree;

      SegTree(int n)
      {
            Size = 1;
            while (Size < n)
                  Size *= 2;

            Default.value = 0;
            tree.assign(2 * Size, Default);
      }

      Node operation(Node x, Node y)
      {
            Node New;
            New.value = x.value + y.value;
            return New;
      }
      void set(int idx, T value, int id, int l, int r)
      {
            if (l == r)
            {
                  tree[id].value = value;
                  return;
            }
            int mid = (l + r) / 2;
            if (idx <= mid)
                  set(idx, value, 2 * id, l, mid);
            else
                  set(idx, value, 2 * id + 1, mid + 1, r);

            tree[id] = operation(tree[2 * id], tree[2 * id + 1]);
      }
      void set(int idx, T value)
      {
            set(idx, value, 1, 1, Size);
      }

      Node get(int lx, int rx, int id, int l, int r)
      {
            if (rx < l || r < lx)
                  return Default;
            if (lx <= l && r <= rx)
            {
                  return tree[id];
            }

            int mid = (l + r) / 2;
            Node x = get(lx, rx, 2 * id, l, mid);
            Node y = get(lx, rx, 2 * id + 1, mid + 1, r);
            return operation(x, y);
      }
      T get(int l, int r)
      {
            return get(l, r, 1, 1, Size).value;
      }
};