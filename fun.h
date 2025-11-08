typedef enum {red, black,doubleblack,white}Color;
typedef enum {left,right}Side;
typedef enum {true,falsh}boll;

#define NULLdata -5

typedef struct node *link;
typedef struct node {
    int data;
    link left ,right ,parent;
    Color color;
    Side side;
}RedBlackTree;

link Initialize();
link InsertKey(link, int);
link RemoveKey(link, int);
void InOrder(link);
boll Search(link,int);