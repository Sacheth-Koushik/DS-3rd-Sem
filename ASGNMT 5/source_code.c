#include<stdio.h>
#include<stdlib.h>


typedef long long ll;

typedef struct node
{
    int data;
    struct node *next;
}
node;

void show(node * start);

void insert(node ** start, int n)
{
    node* temp = (node*)malloc(sizeof(node));
    if(temp == NULL)
    {
        printf("NO MEMORY AAVAILABLE\n");
        return;
    }
    temp -> data = n;
    temp -> next = *start;
    *start = temp;
}


void append(node ** head, int n)
{
    node * temp = (node*)malloc(sizeof(node));
    if(temp == NULL)
    {
        printf("NO MEMORY AAVAILABLE\n");
        return;
    }
    
    temp -> data = n;
    temp -> next = NULL;
    
    if (*head == NULL)
    {
        *head = temp;
        return;
    }
    
    node * it = *head;
    while (it -> next != NULL)
        it = it -> next;
    
    it -> next = temp;
}



node * reverse_iter(node * head)
{
    node * prev = NULL;
    node * curr = head;
    
    while ( curr != NULL)
    {
        node * next = curr -> next; // so that the next node is not lost
        curr -> next = prev; // update the current node
        prev = curr; // the current one becomes the prev for the next one
        curr = next; // move on to the next node
    }
    
    return prev;
    // why is the original list changing to just 1 element after this function is called ?
}


int pop(node ** head)
{
    if(head == NULL)
    {
        printf("THE LIST IS EMPTY\n");
        return 0;
    }
    
    node * tmp = *head;
    *head = (*head)->next;
    return tmp -> data;
}



node * reverse_stack(node * head)
{
    node * a = NULL;
    node * temp = head;
    
    while( temp != NULL )
        insert(&a, pop(&temp));
    
    return a;
}


node * reverse_between(node * head, int m, int n)
{
    if ( m == n )
        return head;
    
    node * curr = head;
    int i = 1;
    
    node *revs = NULL, *rev_prev = NULL;
    node *revend = NULL, *rev_next = NULL;
    
    while ( curr && i <= n)
    {
        if( i < m )
            rev_prev = curr;
        if ( i == m )
            revs = curr;
        if( i == n )
        {
            revend = curr;
            rev_next = curr -> next;
        }
        
        curr = curr -> next;
        i++;
    }
    
    revend -> next = NULL;
    revend = reverse_iter(revs);
    
    if(rev_prev)
        rev_prev -> next = revend;
    else
        head = revend;
    
    revs -> next = rev_next;
    return head;
}


int find(node * head, int n)
{
    int i, data = 0;
    for(i = 1; (i <= n) && head != NULL; i++)
    {
        if (i == n)
            data = head -> data;
        head = head -> next;
    }
    return data;
}


void show(node * start)
{
    node * tmp = start;
    while(tmp != NULL)
    {
        printf("%d -> ", tmp -> data);
        tmp = tmp->next;
    }
    printf("NULL \n");
}

node * pairwise_recur(node * head)
{
    if (head == NULL || head -> next == NULL)
        return head;
    
    node * remaining = head -> next -> next;
    node * new_head = head -> next;
    head -> next -> next = head;
    head-> next = pairwise_recur(remaining);
    return new_head;
}


node * krev(node * head, int k)
{
    node * curr = head;
    node * prev = NULL;
    node * next = NULL;
    int cnt = 0;
    
    //rev k nodes
    while(curr && cnt < k)
    {
        next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
        cnt++;
    }
    
    if(head)
        head -> next = curr;
    
    cnt = 0;
    while(curr && cnt < k)
    {
        curr = curr -> next;
        cnt ++;
    }
    
    if(curr)
        curr -> next = krev(curr -> next, k);
    
    return prev;
}


void middle(node * head)
{
    node * hare = head;
    node * tortoise = head;
    
    
    while(hare && hare -> next)
    {
        hare = hare -> next -> next;
        tortoise = tortoise -> next;
    }
    
    printf("The middle element is [ %d ]\n\n", tortoise -> data);
}


void occurence(node * head, int key, int cnt)
{
    if(head == NULL)
    {
        printf("key %d occurs %d times\n", key, cnt);
        return;
    }
    
    if(head -> data == key)
        cnt ++;
    return occurence(head -> next, key, cnt);
}


node * del_all(node * head, int key)
{
    if(!head)
        return head;
    
    // move away until key is in start
    while(head && head -> data == key)
        head = head -> next;
    
    
    node * curr = head;
    node * prev = NULL;
    
    while(curr)
    {
        if (curr -> data == key)
            prev -> next = curr -> next;
        else
            prev = curr;
        
        curr = curr -> next;
    }
    
    return head;
}


node * merge(node * a, node * b)
{
    node * res = NULL;
    
    if(!a)
        return b;
    else if (!b)
        return a;
    
    if(a -> data <= b -> data)
    {
        res = a;
        res -> next = merge(a -> next, b);
    }
    else
    {
        res = b;
        res -> next = merge(a, b ->  next);
    }
    
    return res;
}


void multiply_add(node * a, node * b)
{
    ll n1 = 0, n2 = 0, mod = 1000000007;
    
    while(a || b)
    {
        if(a)
        {
            n1 = (n1 * 10) % mod + a -> data;
            a = a -> next;
        }
        if(b)
        {
            n2 = (n2 * 10) % mod + b -> data;
            b = b -> next;
        }
    }
    
    ll res = (n1 * n2) % mod;
    printf("The numbers are %lld, %lld\n", n1, n2);
    printf("the sum is %lld\n", n1 + n2);
    printf("The product is %lld\n", res);
    
}


node * intersection(node * a, node * b)
{
    node * ptr1 = a;
    node * ptr2 = b;
    
    if(!ptr1 || !ptr2)
        return NULL;
    
    while(ptr1 != ptr2)
    {
        ptr1 = ptr1 -> next;
        ptr2 = ptr2 -> next;
        
        if(ptr1 == ptr2)
            return ptr1;
        
        if(!ptr1)
            ptr1 = b;
        if(!ptr2)
            ptr2 = a;
    }
     
    return ptr1;
}


void partition(node ** head, int x)
{
    // make 3 lists for smaller, equal, greater ele
    node * smaller_head = NULL; node * smaller_last = NULL;
    node * equal_head = NULL; node * equal_last = NULL;
    node * greater_head = NULL; node * greater_last = NULL;
    
    node * tmp = *head;
    
    while(tmp)
    {
        if(tmp -> data == x)
        {
            if(equal_head == NULL)
                equal_head = equal_last = tmp;
            else
            {
                equal_last -> next = tmp;
                equal_last = equal_last -> next;
            }
        }
        else if(tmp -> data < x)
        {
            if(smaller_head == NULL)
                smaller_head = smaller_last = tmp;
            else
            {
                smaller_last -> next = tmp;
                smaller_last = tmp;
            }
        }
        else
        {
            if(greater_head == NULL)
                greater_head = greater_last = tmp;
            else
            {
                greater_last -> next = tmp;
                greater_last = tmp;
            }
        }
        
        tmp = tmp -> next;
    }
    
    if(!smaller_head)
    {
        if(!equal_head)
        {
            *head = greater_head;
            return;
        }
        equal_last -> next = greater_head;
        * head = equal_head;
        return;
    }
    
    if(!equal_head)
    {
        smaller_last -> next = greater_head;
        * head = smaller_head;
        return;
    }
    
    smaller_last -> next = equal_head;
    equal_last -> next = greater_head;
    *head = smaller_head;
}

int main(void)
{
    node * a = NULL;append(&a,1);append(&a,2);append(&a,3);append(&a,4);append(&a,5);append(&a,6);append(&a,7);
    node * b = NULL;append(&b,1);append(&b,2);append(&b,3);append(&b,4);append(&b,5);append(&b,6);append(&b,7);
    node * c = NULL;append(&c,1);append(&c,2);append(&c,3);append(&c,4);append(&c,5);append(&c,6);append(&c,7);
    node * d = NULL;append(&d,1);append(&d,2);append(&d,3);append(&d,4);append(&d,5);append(&d,6);append(&d,7);
    node * e = NULL;append(&e,1);append(&e,2);append(&e,3);append(&e,4);append(&e,5);append(&e,6);append(&e,7);
    node * f = NULL;append(&f,1);append(&f,2);append(&f,3);append(&f,4);append(&f,5);append(&f,6);append(&f,7);
    
    // (1) reverse array by stack method
    printf("\nBY STACK\n");
    printf("list is\n");
    show(a);
    node * arev_stack = reverse_stack(a);
    show(arev_stack);
    
    // (1) Rverse array by iterative method
    printf("\nBY ITER\n");
    printf("list is\n");
    show(b);
    node * brev_iter = reverse_iter(b);
    show(brev_iter);
    
    // (2) reverse a sub-link list
    // 1 based indexing
    printf("CHANGE\n");
    printf("list is\n");
    show(c);
    node * revc = reverse_between(c, 2, 5);
    show(revc);
    
    // (3) find nth node, 1 based indexing
    printf("6th node is: %d\n", find(d, 1));
    
    // (4) swap pairwise of the nodes
    printf("pairwise\n");
    printf("list is\n");
    show(d);
    node * d_pair = pairwise_recur(d);
    show(d_pair);
    
    //(5) to alternately reverse k nodes
    printf("\nKREV\n");
    printf("list is\n");
    show(e);
    node * ekrev = krev(e, 3);
    show(ekrev);
    
    //(6) middle of linked list
    printf("\nList is : \n");
    show(f);
    middle(f);
    
    //(7) count occurence of key
    printf("\nList is\n");
    append(&f, 1);append(&f, 1);append(&f, 1);append(&f, 1);append(&f, 1);append(&f, 1);append(&f, 1);append(&f, 1);
    
    show(f);
    occurence(f, 1, 0);
    
    //(8) delete all occurences of a key in given list
    printf("\nThe list is \n");
    show(f);
    node * deled = del_all(f, 1);
    show(deled);
    
    //(9) merge two sorted linked lists
    printf("The lists are\n");
    show(f);
    show(e);
    node * merged = merge(f,e);
    show(merged);
    
    //(10) (11) multiply the nums
    node * fst = NULL;
    node * snd = NULL;
    append(&fst, 1);append(&fst, 2);append(&fst, 3);append(&fst, 4);append(&fst, 5);append(&fst, 6);
    append(&snd, 1);append(&snd, 2);append(&snd, 3);
    multiply_add(fst, snd);
    
    
    //(12) intersection point of two lists
    printf("\nTwo lists are\n");
    snd -> next -> next -> next = fst -> next -> next -> next;
    node * inter = intersection(fst, snd);
    show(fst);
    show(snd);
    show(inter);
    
    //(13) sort the link list plainly
    node * g = NULL;
    append(&g, 10);append(&g, 4);append(&g, 5);append(&g, 30);append(&g, 2);append(&g, 50);
    printf("The list is\n");
    show(g);
    partition(&g, 5);
    printf("After partition\n");
    show(g);
    
    
    return 0;
}
