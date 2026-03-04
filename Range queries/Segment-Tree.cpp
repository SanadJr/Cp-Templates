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

      Node merge(Node x, Node y)
      {
            Node New;
            New.value = x.value + y.value;
            return New;
      }
      void set(int idx, T value, int id, int lx, int rx)
      {
            if ( lx == rx )
            {
                  tree[id].value = value;
                  return;
            }
            int mid = (lx + rx) / 2;
            if (idx <= mid)
                  set(idx, value, 2 * id, lx, mid);
            else
                  set(idx, value, 2 * id + 1, mid + 1, rx);

            tree[id] = merge(tree[2 * id], tree[2 * id + 1]);
      }
      void set(int idx, T value)
      {
            set(idx, value, 1, 1, Size);
      }

      Node get(int l, int r, int id, int lx, int rx)
      {
            if ( rx < l || lx > r )
                  return Default;
            if ( lx >= l && rx <= r )
            {
                  return tree[id];
            }

            int mid = (lx + rx) / 2;
            Node x = get(l, r, 2 * id, lx, mid);
            Node y = get(l, r, 2 * id + 1, mid + 1, rx);
            return merge(x, y);
      }
      T get(int l, int r)
      {
            return get(l, r, 1, 1, Size).value;
      }
};