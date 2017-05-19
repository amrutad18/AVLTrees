#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define SIZE 10
typedef struct Tree_tag
{
    struct Tree_tag*left;
    struct Tree_tag*right;
    int key;
    int bf;
    int leftsub;
    int rightsub;
}TreeNode;
//This function finds the height of each node of an AVL tree
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

TreeNode* Insert_AVL(TreeNode* root,int key)
{
    TreeNode* ptr,*temp=root;
    ptr=(TreeNode*)malloc(sizeof(TreeNode));//This can be wrapped in a function
    ptr->left=NULL;
    ptr->right=NULL;
    ptr->bf=0;
    ptr->key=key;
    if(root==NULL)
    {
        root=ptr;
    }
    else
    {
        if(key<root->key)
        {
            (root->left)=Insert_AVL(root->left,key);
            root->bf=HeightOfTree(root->left)-HeightOfTree(root->right);
        }
        else if(key > root->key)
        {
            root->right=Insert_AVL(root->right,key);
            root->bf=HeightOfTree(root->left)-HeightOfTree(root->right);
        }
    }
    root=BalanceTree(root);
    return root;
}

void Preorder(TreeNode*root)
{
    if(root!=NULL)
    {
        printf("key:%d ",root->key);
        printf("left:%d ,right=%d\n",root->leftsub,root->rightsub);
	Preorder(root->left);
        order(root->right);
    }
}


//This function finds the total nodes present in each root
int TotalNodes(TreeNode* root)
{
    int retval;
    if(root==NULL)
    {
        retval=0;
    }
    else
    {
        retval=1+TotalNodes(root->left)+TotalNodes(root->right);
    }
    return retval;
}

//This function finds the number of nodes present in the right and left subtree of each node of the AVL tree
void CountSubTree(TreeNode*root)
{
    if(root!=NULL)
    {
        root->leftsub=TotalNodes(root->left);
        root->rightsub=TotalNodes(root->right);
        CountSubTree(root->left);
        CountSubTree(root->right);
    }
}

int CountAll(int k1,int k2,TreeNode*root)
{
    int count=0;
    TreeNode*tempR,*tempL;
    if(root!=NULL)
    {

        //If root is less than k1 we don't check the left subtree as it will never be in the range
        //Instead we call the same function with the right child as parameter
        if(root->key <= k1)
        {
            count=CountAll(k1,k2,root->right);
        }
        //If root is greater than k2 then we don't check in the right sub tree as no node in the right subtree will be in the range
        //We call the same function with the left child as parameter
        else if(root->key>=k2)
        {
            count=CountAll(k1,k2,root->left);
        }
        //Here we find the first node which is between k1 and k2
        //All the nodes to the left of this node will be less than k2 whereas all the nodes to the right will be greater than k1
        //So this node+ the number of nodes in the left subtree greater than k1+ number of nodes in the right subtree less than k2 will
        //give total count.
        else if(root->key <k2&&root->key>k1)
        {
            count=1;
            TreeNode*temp=root->left;
            //We check the left subtree for all nodes greater than k1
            //If the root of the left subtree is less than or equal to k1.We go on checking in its right child
            //Once we find a node in the right side which is greater than k1, all its right nodes are also going
            //to be greater than k1 so we simply add all the right nodes it contains to our count
	    if(temp!=NULL)
            {
            	if(temp->key<=k1)
            	{
                	tempR=temp->right;
                	while(tempR!=NULL&&tempR->key<=k1)
                	{
                    	tempR=tempR->right;
                	}
                	if(tempR!=NULL)
                	{
                    	count=1+count+tempR->rightsub;
                	}
            	}
            //If the root of the left subtree is less than k1 we know that all nodes in its right side
            //are going to be greater than k1 so we go on simply add all nodes to its right
            //Similarly we go in checking this for all its left children until we reach null or key is less than k1
            	else
            	{
                	while(temp!=NULL&&temp->key>k1)
               	 	{
                    	count=count+temp->rightsub+1;
                    	temp=temp->left;
                	}
			if(temp!=NULL)
			{
				if(temp->right!=NULL)
				{
					if((temp->right)->key>k1)
					{
						count=count+temp->rightsub;
					}
				}
			}
            	}
	     }

            //We do the symmetric operation in the right subtree
            temp=root->right;
	    if(temp!=NULL)
	    {
            	if(temp->key>=k2)
            	{
                	tempL=temp->left;
                	while(tempL!=NULL&&tempL->key>=k2)
                	{
                    	tempL=tempL->left;
                	}
                	if(tempL!=NULL)
                	{
                    	count=1+count+tempL->leftsub;
                	}
            	}
            	else
           	 {
                	while(temp!=NULL&&temp->key<k2)
               	 	{
                    	count=count+1+temp->leftsub;
                    	temp=temp->right;
                	}
			if(temp!=NULL)
			{
				if(temp->left!=NULL)
				{
					if((temp->left)->key<k2)
					{
						count=count+temp->leftsub;
					}
				}
			}
            	}
           }
        }
    }
    return count;
}

int main()
{
    char word[SIZE];
    int k,select=-1;
    TreeNode*ptr=NULL;
    FILE *fp=fopen("input.txt","r");
    int flag=1;
    while(flag==1)
    {
	flag=fscanf(fp,"%d",&k);
	if(flag==1)
	{
		ptr=Insert_AVL(ptr,k);
	}
    }
    CountSubTree(ptr);
    TreeNode*temp=ptr;
    Preorder(temp);
    printf("\n\n");
    int k1,k2;
    printf("Enter k1 and k2\n");
    scanf("%d%d",&k1,&k2);
    printf("Count:%d\n\n",CountAll(k1,k2,ptr));
    return 0;
}

