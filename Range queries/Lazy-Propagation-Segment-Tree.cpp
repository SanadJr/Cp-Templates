template <typename T>
class SegTree
{
public:
      struct Node
      {
            T value;
            T lazy ;
            bool is_lazy ;

            void change( int v, int lx, int rx )
            {
                  value += v * ( rx - lx + 1 ) ;
                  lazy += v ;
                  is_lazy = 1 ;
            }
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
            Default.lazy = 0;
            Default.is_lazy = 0;
            tree.assign(2 * Size, Default);
      }

      void progagate( int id, int lx, int rx )
      {
            if ( tree[id].is_lazy == 0 || lx == rx )
                  return ;

            int mid = ( lx + rx ) / 2 ;
            tree[ 2 * id ].change( tree[id].lazy, lx, mid ) ;
            tree[ 2 * id + 1 ].change( tree[id].lazy, mid+1, rx ) ;

            tree[id].lazy = 0 ;
            tree[id].is_lazy = 0 ;
      }
      Node merge(Node x, Node y)
      {
            Node New = Default ;
            New.value = x.value + y.value;
            return New;
      }
      void set( int l, int r, T value, int id, int lx, int rx )
      {
            progagate( id, lx, rx ) ;

            if ( rx < l || lx > r )
                  return ;
            if ( lx >= l && rx <= r )
            {
                  tree[id].change( value, lx, rx ) ;
                  return ;
            }

            int mid = (lx + rx) / 2 ;
            
            set( l, r, value, 2 * id, lx, mid) ;
            set( l, r, value, 2 * id + 1, mid + 1, rx) ;

            tree[id] = merge(tree[2 * id], tree[2 * id + 1]) ;
      }
      void set( int l, int r, T value )
      {
            set( l, r, value, 1, 1, Size ) ;
      }

      Node get(int l, int r, int id, int lx, int rx)
      {
            progagate( id, lx, rx ) ;
            
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