#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<graphics.h>

using namespace std;

struct node
{
    int data;
    char colour;
    node *left,*right,*parent;
};

node *root=NULL;

void bothred(node *g,node *u,node *p)
{
    if(g!=root)
        g->colour='r';
    u->colour='b';
    p->colour='b';
}

void uncleblack(node *g,node *u,node *p,node *c)
{
         if(((g->left==u)||(g->left==NULL))&&p->left==c)
         {
             g->right=c;
             c->parent=g;
             p->left=c->right;
             c->right=p;
             p->parent=c;
             swap(p,c);
         }
         if(((g->right==u)||(g->right==NULL))&&p->right==c)
         {
             g->left=c;
             c->parent=g;
             p->right=c->left;
             c->left=p;
             p->parent=c;
             swap(p,c);
         }
         if(g->right==p&&p->right==c)
         {
             g->right=p->left;
             node *sumner=p->left;
             if(sumner!= NULL)
                 sumner->parent=g;
             p->left=g;
             p->parent=g->parent;
             if(g!=root)
             {
                 if((g->parent)->right==g)
                    (g->parent)->right=p;
                 if((g->parent)->left==g)
                    (g->parent)->left=p;
             }
             g->parent=p;
             if(g==root)
                root=p;
             swap(p->colour,g->colour);
             swap(p,g);
         }
         if(g->left==p&&p->left==c)
         {
             g->left=p->right;
             node *sumne=p->right;
             if(sumne != NULL)
                 sumne->parent=g;
             p->right=g;
             p->parent=g->parent;
             if(g!=root)
             {
                 if((g->parent)->right==g)
                    (g->parent)->right=p;
                 if((g->parent)->left==g)
                    (g->parent)->left=p;
             }
             g->parent=p;
             if(g==root)
                root=p;
             swap(p->colour,g->colour);
             swap(p,g);
         }
}
void checkfunction(node *child)
{
    node *gramps=NULL,*par=NULL,*uncle=NULL;
    par=child->parent;
    if(par==NULL)
        return;
    gramps=(par)->parent;
    if(gramps!=NULL)
    {
        if(gramps->left==par)
            uncle=(gramps)->right;
        else
            uncle=(gramps)->left;
        if(uncle!=NULL)
        {
            if(uncle->colour=='r'&&par->colour=='r'&&child->colour=='r')
                bothred(gramps,uncle,par);
            if(uncle->colour=='b'&&par->colour=='r'&&child->colour=='r')
                uncleblack(gramps,uncle,par,child);
        }
        if(uncle==NULL)
            uncleblack(gramps,uncle,par,child);
    }
}
void preorder(node *ptr)
{
    node *temp=new node;
    temp=ptr;
    if(temp!=NULL)
    {
        checkfunction(temp);
        preorder(temp->left);
        preorder(temp->right);
    }
}
void inorder(node *ptr)
{
    node *temp=new node;
    temp=ptr;
    if(temp!=NULL)
    {
        inorder(temp->left);
        cout<<"\t\t\t\t\t\t\t\t\t                  ";
        cout<<left<<setw(10)<<temp->data<<left<<setw(10)<<temp->colour;
        if(temp!=root)
        {
            cout<<left<<setw(10)<<(temp->parent)->data<<endl;
        }
        else
            cout<<endl;
        inorder(temp->right);
    }
}
void insertnode()
{
    node*par=NULL;
    node* newnode=new node;
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t                  Enter the value of new node to be inserted:";
    cin>>newnode->data;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->parent=NULL;
    newnode->colour='r';
    if(root==NULL)
    {
        root=newnode;
        root->colour='b';
        cout<<"\n\n\n\t\t\t\t\t\t\t                  Root value : "<<newnode->data<<endl;
        return;
    }
    else
    {
        node *cur=root;
        while(cur!=NULL)
        {
            par=cur;
            if(newnode->data>cur->data)
                cur=cur->right;
            else
                if(newnode->data<cur->data)
                    cur=cur->left;
                else
                {
                    cout<<"\n\n\n\t\t\t\t\t\t\t                  Node "<<newnode->data<<" already present.."<<endl;
                    return;
                }
        }
        if(newnode->data>par->data)
        {
            par->right=newnode;
            newnode->parent=par;
        }
        else
        {
            par->left=newnode;
            newnode->parent=par;
        }
        checkfunction(newnode);
        preorder(root);
        cout<<"\n\n\n\t\t\t\t\t\t\t                  Node "<<newnode->data<<" successfully inserted..."<<endl;
    }
    return;
}
void eliminatedb(node *elnode);
void dpreorder(node *ptr)
{
    node *temp=new node;
    temp=ptr;
    if(temp!=NULL)
    {
        if(temp->colour=='d')
            eliminatedb(temp);
        dpreorder(temp->left);
        dpreorder(temp->right);
    }
}
void siblingred(char pos,node *elnode)
{
        node *db=elnode;
        node *g=db->parent;
        node *p=NULL,*pl=NULL,*pt=NULL;
        if(db==g->left)
            p=g->right;
        else
            if(db==g->right)
                p=g->left;
        swap(p->colour,g->colour);
        if(pos=='r')
        {
            pl=p->right;
            pt=p->left;
            g->right=p->left;
            node *sumner=p->left;
            if(sumner!= NULL)
                sumner->parent=g;
            p->left=g;
            p->parent=g->parent;
            if(g!=root)
            {
                if((g->parent)->right==g)
                    (g->parent)->right=p;
                if((g->parent)->left==g)
                    (g->parent)->left=p;
            }
            g->parent=p;
            if(g==root)
                root=p;
            dpreorder(root);
        }
        if(pos=='l')
        {
            pl=p->left;
            pt=p->right;
            g->left=p->right;
            node *sumne=p->right;
            if(sumne != NULL)
                sumne->parent=g;
            p->right=g;
            p->parent=g->parent;
            if(g!=root)
            {
                if((g->parent)->right==g)
                    (g->parent)->right=p;
                if((g->parent)->left==g)
                    (g->parent)->left=p;
            }
            g->parent=p;
            if(g==root)
                root=p;
            dpreorder(root);
        }
}
void linered(char pos,node *elnode)
{
    node *db=elnode;
    node *g=db->parent;
    node *p=NULL,*pl=NULL,*pt=NULL;
    if(db==g->left)
        p=g->right;
    else
        if(db==g->right)
            p=g->left;
    swap(g->colour,p->colour);
    if(pos=='r')
    {
        pl=p->right;
        pt=p->left;
        g->right=p->left;
        node *sumner=p->left;
        if(sumner!= NULL)
            sumner->parent=g;
        p->left=g;
        p->parent=g->parent;
        if(g!=root)
        {
            if((g->parent)->right==g)
                (g->parent)->right=p;
            if((g->parent)->left==g)
                (g->parent)->left=p;
        }
        g->parent=p;
        if(g==root)
            root=p;
        if(db->data==-1111)
        {
            if((db->parent)->left==db)
                (db->parent)->left=NULL;
            else
                (db->parent)->right=NULL;
            delete(db);
        }
    }
    if(pos=='l')
    {
        pl=p->left;
        pt=p->right;
        g->left=p->right;
        node *sumne=p->right;
        if(sumne != NULL)
            sumne->parent=g;
        p->right=g;
        p->parent=g->parent;
        if(g!=root)
        {
            if((g->parent)->right==g)
                (g->parent)->right=p;
            if((g->parent)->left==g)
                (g->parent)->left=p;
        }
        g->parent=p;
        if(g==root)
            root=p;
        if(db->data==-1111)
        {
            if((db->parent)->left==db)
                (db->parent)->left=NULL;
            else
                (db->parent)->right=NULL;
            delete(db);
        }
    }
    pl->colour='b';
}
void trianglered(char pos,node *elnode)
{
    node *db=elnode;
    node *g=db->parent;
    node *p=NULL,*pl=NULL,*pt=NULL;
    if(db==g->left)
        p=g->right;
    else
        if(db==g->right)
            p=g->left;
    if(pos=='r')
    {
        pl=p->right;
        pt=p->left;
        g->right=pt;
        pt->parent=g;
        p->left=pt->right;
        pt->right=p;
        p->parent=pt;
    }
    if(pos=='l')
    {
        pl=p->left;
        pt=p->right;
        g->left=pt;
        pt->parent=g;
        p->right=pt->left;
        pt->left=p;
        p->parent=pt;
    }
    swap(p->colour,pt->colour);
    linered(pos,elnode);
}
void eliminatedb(node *elnode)
{
    node *db=elnode;
    if(db==root)
    {
        db->colour='b';
        return;
    }
    node *g=db->parent;
    node *p=NULL,*pl=NULL,*pt=NULL;
    char flag;
    if(db==g->left)
    {
        p=g->right;
        flag='r';
        if(p!=NULL)
        {
            pl=p->right;
            pt=p->left;
        }
    }
    else
        if(db==g->right)
        {
            p=g->left;
            flag='l';
            if(p!=NULL)
            {
                pl=p->left;
                pt=p->right;
            }
        }
    if(p!=NULL)
    {
        if(p->colour=='r')
        {
            siblingred(flag,db);
        }
        else if(p->colour=='b')
        {
            if(pt!=NULL)
            {
                if(pt->colour=='r')
                {
                    trianglered(flag,db);
                }
            }
            else if(pl!=NULL)
            {
                if(pl->colour=='r')
                {
                    linered(flag,db);
                }
            }
            else if((pl==NULL&&pt==NULL)||(pl->colour=='b'&&pt->colour=='b')||(pl==NULL&&pt->colour=='b')||(pt==NULL&&pl->colour=='b'))
            {
                db->colour='b';
                p->colour='r';
                if(g->colour=='r')
                    g->colour='b';
                else if(g->colour=='b')
                    g->colour='d';
                if(db->data==-1111)
                {
                    if((db->parent)->left==db)
                        (db->parent)->left=NULL;
                    else
                        (db->parent)->right=NULL;
                    delete(db);
                }
                if(g->colour=='d')
                    eliminatedb(g);
            }
        }
    }
    else if((p==NULL)||(p->colour=='b'&&pl->colour=='b'&&pt->colour=='b'))
    {
        if(flag=='r')
            g->left=NULL;
        else
            if(flag=='l')
                g->right=NULL;
        db->colour='b';
        if(g->colour=='r')
            g->colour='b';
        else if(g->colour=='b')
            g->colour='d';
        if(p!=NULL)
            p->colour='r';
        if(db->data==-1111)
        {
            if((db->parent)->left==db)
                (db->parent)->left=NULL;
            else
                (db->parent)->right=NULL;
            delete(db);
        }
        if(g->colour=='d')
            eliminatedb(g);
    }
}
void findpredorsuc(node *del)
{
    node *predecessor=NULL,*successor=NULL,*temp=NULL;
    if(del->left==NULL)
    {
        if(del->right!=NULL)
            successor=del->right;
        else
            {
                if(del!=root)
                {
                    if(del->colour=='b')
                    {
                        del->colour='d';
                        temp=del;
                        temp->data=-1111;//eyes on this.
                        eliminatedb(temp);
                    }
                    else if(del->colour=='r')
                    {
                        if((del->parent)->left==del)
                            (del->parent)->left=NULL;
                        else
                            (del->parent)->right=NULL;
                        delete(del);
                    }
                }
                else if(del==root)
                    delete(del);
            }
    }
    else
        predecessor=del->left;
    if(predecessor!=NULL)
    {
        while(predecessor!=NULL)
        {
            temp=predecessor;
            predecessor=predecessor->right;

        }
        swap(temp->data,del->data);
        if(temp->colour=='r')
        {
            if((temp->parent)->left==temp)
                (temp->parent)->left=NULL;
            else
                (temp->parent)->right=NULL;
            delete(temp);
        }
        if(temp->colour=='b')
        {
            temp->colour='d';
            temp->data=-1111;
            eliminatedb(temp);
        }
    }
    if(successor!=NULL)
    {
        while(successor!=NULL)
        {
            temp=successor;
            successor=successor->left;
        }
        swap(temp->data,del->data);
        if(temp->colour=='r')
        {
            if((temp->parent)->left==temp)
                (temp->parent)->left=NULL;
            else
                (temp->parent)->right=NULL;
             delete(temp);
        }
        if(temp->colour=='b')
        {
            temp->colour='d';
            temp->data=-1111;
            eliminatedb(temp);
        }
    }
}
void deletenode()
{
    int dn;
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t                  Enter the node to be deleted:";
    cin>>dn;
    node *temp=root;
    while(temp!=NULL)
    {
        if(dn==temp->data)
            break;
        else
            if(dn>temp->data)
                temp=temp->right;
            else
                if(dn<temp->data)
                    temp=temp->left;

    }
    if(temp!=NULL)
    {
        findpredorsuc(temp);
        cout<<"\n\n\n\t\t\t\t\t\t\t\t\t                  Node "<<dn<<" deleted successfully"<<endl;
        if(temp==root&&temp->left==NULL&&temp->right==NULL)
            root=NULL;
    }
    else
    {
        cout<<"Node not present...";
        return;
    }
}
int main()
{
    system("cls");
    system("COLOR 04");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t     -------------------------------------------"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t     |ADA Open Ended Project on RED-BLACK TREES|"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t     -------------------------------------------"<<endl;
    delay(10000);
    system("cls");
    int choice=1;
    int chc;
    while(choice)
    {
        system("cls");
        system("COLOR 04");
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t                  1.INSERT\n\n\t\t\t\t\t\t\t\t\t                  2.DELETE\n\n\t\t\t\t\t\t\t\t\t                  3.DISPLAY\n\n\n\t\t\t\t\t\t\t\t Enter your choice:";
        cin>>chc;
        if(chc==1)
        {
            system("cls");
            insertnode();
        }
        if(chc==2)
        {
             system("cls");
            deletenode();
        }
        if(chc==3)
        {
             system("cls");
             cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t                  ";
             if(root==NULL)
                cout<<"Empty tree...."<<endl;
             else
             {
                cout<<left<<"\t"<<setw(10)<<"Value"<<left<<setw(10)<<"Colour"<<left<<setw(10)<<"Parent"<<endl<<endl;
                inorder(root);
             }
        }
        cout<<"\n\n\n\t\t\t\t\t\t\t\t\t                  Do you want to continue:";
        cin>>choice;
        system("cls");
    }
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t                  Thank you for using this code"<<endl;
    return 0;
}
