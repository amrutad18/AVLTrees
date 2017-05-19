#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct Tree_tag
{
    struct Tree_tag*left;
    struct Tree_tag*right;
    int bf;//balance Factor of the AVL TREE Try this with enum
    int data;//Data node, 
}TreeNode;

//This function calculates the height of a tree. It is used in calculating balance factor for nodes in AVL trees

int HeightOfTree(TreeNode* treeptr)
{
    int height=-1;
    int l,r;
    if(treeptr!=NULL)
    {
        if(treeptr->left==NULL&&treeptr->right==NULL)
        {
            height=0;
        }
        else
        {
            l=HeightOfTree(treeptr->left);
            r=HeightOfTree(treeptr->right);
            if(l>r)
            {
                height=l+1;
            }
            else
            {
                height=r+1;
            }
        }
    }
    return height;
}

TreeNode* RotateLeft(TreeNode*p)
{
    TreeNode* temp=p;
    if(p==NULL)
    {
        printf("Error3!\n");
    }
    else if(p->right==NULL)
    {
        printf("Error4!\n");
    }
    else
    {
        temp=p->right;
        p->right=temp->left;
        temp->left=p;
        temp->bf=HeightOfTree(temp->left)-HeightOfTree(temp->right);
        p->bf=HeightOfTree(p->left)-HeightOfTree(p->right);
    }

    return temp;
}

TreeNode* RotateRight(TreeNode*p)
{
    TreeNode* temp=p;
    if(p==NULL)
    {
        printf("Error1!\n");
    }
    else if(p->left==NULL)
    {
        printf("Error2!\n");
    }
    else
    {
        temp=p->left;
        p->left=temp->right;
        temp->right=p;
        temp->bf=HeightOfTree(temp->left)-HeightOfTree(temp->right);
        p->bf=HeightOfTree(p->left)-HeightOfTree(p->right);
    }
    return temp;
}

TreeNode* BalanceTree(TreeNode*root)
{
    if(root->bf==2&&(root->left)->bf==1)
    {
        root=RotateRight(root);
    }
    else if(root->bf==2&&(root->left)->bf==-1)
    {
        root->left=RotateLeft(root->left);
        root=RotateRight(root);

    }
    else if(root->bf==-2&&(root->right)->bf==-1)
    {
        root=RotateLeft(root);
    }
    else if(root->bf==-2&&(root->right)->bf==1)
    {
        root->right=RotateRight(root->right);
        root=RotateLeft(root);
    }
    return root;
}
//This function inserts a node in an AVL tree and also updates its balance factor

TreeNode* Insert_AVL(TreeNode* root,int d)
{
    TreeNode* ptr,*temp=root;
    ptr=(TreeNode*)malloc(sizeof(TreeNode));//This can be wrapped in a function
    ptr->data=d;
    ptr->left=NULL;
    ptr->right=NULL;
    ptr->bf=0;
    if(root==NULL)
    {
        root=ptr;
    }
    else
    {
        if(d < root->data)
        {
            (root->left)=Insert_AVL(root->left,d);
            root->bf=HeightOfTree(root->left)-HeightOfTree(root->right);
        }
        else if(d>root->data)
        {
            root->right=Insert_AVL(root->right,d);
            root->bf=HeightOfTree(root->left)-HeightOfTree(root->right);
        }
    }
    root=BalanceTree(root);
    return root;
}


TreeNode* Delete_AVLR(TreeNode*treeptr)
{
    TreeNode*ptr=treeptr;
    TreeNode*temp;
    if(ptr==NULL)
    {
        printf("Error!\n");
    }
    else if(treeptr->right==NULL)
    {
        temp=treeptr;
        treeptr=treeptr->left;
        free(temp);
    }
    else
    {
        ptr->right=Delete_AVLR(ptr->right);
        ptr->bf=HeightOfTree(ptr->left)-HeightOfTree(ptr->right);
        treeptr=BalanceTree(treeptr);
    }
    return treeptr;
}

TreeNode* Delete_AVLL(TreeNode*treeptr)
{
    TreeNode*ptr=treeptr;
    TreeNode*temp;
    if(ptr==NULL)
    {
        printf("Error!\n");
    }
    else if(treeptr->left==NULL)
    {
        temp=treeptr;
        treeptr=treeptr->right;
        free(temp);
    }
    else
    {
        ptr->left=Delete_AVLL(ptr->left);
        ptr->bf=HeightOfTree(ptr->left)-HeightOfTree(ptr->right);
        treeptr=BalanceTree(treeptr);
    }
    return treeptr;
}

void PreorderFile(TreeNode*root,FILE*optr)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        printf("bf:%d \n",root->bf);
        fprintf(optr,"%d ",root->data);
	PreorderFile(root->left,optr);
        PreorderFile(root->right,optr);
    }
}

void PreOrder(TreeNode*root)
{
	if(root!=NULL)
	{
		printf("%d ",root->data);
		printf("bf:%d\n",root->bf);
		PreOrder(root->left);
		PreOrder(root->right);
	}
}


TreeNode* UpdateBalanceFactor(TreeNode* root)
{
    if(root!=NULL)
    {
        root->bf=HeightOfTree(root->left)-HeightOfTree(root->right);
        root->left=UpdateBalanceFactor(root->left);
        root->right=UpdateBalanceFactor(root->right);
    }
    return root;
}
int main()
{
    int select=-1;
    int data;
    int h1,h2,flag=1;
    TreeNode*ptr1=NULL,*ptr2=NULL;
    FILE*fp1=fopen("input.txt","r");
    FILE *optr=fopen("output.txt","w");
    while(flag==1)
    {
	flag = fscanf(fp1, "%d", &data);
        if(flag==1)
        {
        	ptr1=Insert_AVL(ptr1,data);
	}
    }
    fclose(fp1);
    FILE*fp2=fopen("input2.txt","r");
    flag=1;
    while(flag==1)
    {
	flag=fscanf(fp2, "%d", &data);
        if(flag==1)
        {
	  ptr2=Insert_AVL(ptr2,data);
	}
    }
    fclose(fp2);
    h1=HeightOfTree(ptr1);
    h2=HeightOfTree(ptr2);
    TreeNode*temp;
    TreeNode*root,*root1;
    PreOrder(ptr1);
    printf("\n");
    PreOrder(ptr2);
    printf("\n");
    if(h2>=h1)
    {//See if you can include in delete function
        temp=ptr1;
        while(temp->right!=NULL)
        {
            temp=temp->right;
        }
    //We go rightwards in T1 and find the largest node,we store its value in a new root and delete the node
    //Now all the nodes in the remaining tree T1 are going to be less than its largest node(The node deleted)
        root1=(TreeNode*)malloc(sizeof(TreeNode));
        root1->data=temp->data;
        root1->left=NULL;
        root1->right=NULL;
        ptr1=Delete_AVLR(ptr1);
        h1=HeightOfTree(ptr1);
        root1->left=ptr1;
        //We make the root of T1 as the left child of the new node
        //To make this an AVL tree the right child should have a height equal to that of left subtree
        //or 1 greater than height of left sub tree
        //In the tree 2 we go leftwards until we find a node that satisfies this
        TreeNode*temp2=ptr2,*prev=NULL;
        while(HeightOfTree(temp2)>h1+1&&temp2->left!=NULL)
        {
            prev=temp2;
            temp2=temp2->left;
        }
        //We also keep track of its parent(prev)
        //We attach this node as right child of new node
        root1->right=temp2;
        root1->bf=HeightOfTree(root1->left)-HeightOfTree(root1->right);
        root1=BalanceTree(root1);
        //If that node has no parent the new node is the root of the union of t1 and t1
        if(prev==NULL)
        {
            root=root1;
        }
        //If its parent is not null we attach the new node as left child of this parent
        //Now the root of T2 is root of the union of the AVL trees
        else
        {
            prev->left=root1;
            root=ptr2;
        }
    }
    //If h2<h1 the case is symmetric
    else
    {
        temp=ptr2;
        while(temp->left!=NULL)
        {
            temp=temp->left;
        }
        root1=(TreeNode*)malloc(sizeof(TreeNode));
        root1->data=temp->data;
        root1->left=NULL;
        root1->right=NULL;
        ptr2=Delete_AVLL(ptr2);
        h2=HeightOfTree(ptr2);
        root1->right=ptr2;
        TreeNode*temp2=ptr1,*prev=NULL;
        while(HeightOfTree(temp2)>h2+1&&temp2->right!=NULL)
        {
            prev=temp2;
            temp2=temp2->right;
        }
        root1->left=temp2;
        root1->bf=HeightOfTree(root1->left)-HeightOfTree(root1->right);
        root1=BalanceTree(root1);
        if(prev==NULL)
        {
            root=root1;
        }
        else
        {
            prev->right=root1;
            root=ptr1;
        }
    }
    root=UpdateBalanceFactor(root);
    //root->bf=HeightOfTree(root->left)-HeightOfTree(root->right);
    root=BalanceTree(root);
    PreorderFile(root,optr);
    fclose(optr);
    return 0;
}
