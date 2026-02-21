#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <time.h>

                      /*ان شاء الله العلامة الكاملة*/


//heba dababat
//1230151
//sec 3

#define GraphSize 300  // number of minimum edges
#define order 100       // number of cities (vertices)

// Heaps structure -----------------------------------------
typedef struct MinHeap* heap;

typedef struct HeapNode{
    char src_city[30];
    char dest_city[30];
    int distance;
}HeapNode;

typedef struct MinHeap{
    HeapNode *HeapArray;
    int size;
    int capacity;
}MinHeap;
//Graph structer using adjacency list(array of lists)-------------------------------------------
typedef struct Graph* graph;
typedef struct Edge{
    char src[30];   //source city
    char dest[30];   // destination city
    int weight;     //distance
    struct Edge* next;

} Edge;

typedef struct List{
    Edge* head;  //head of each list in the array
}List;

typedef struct Graph{
    int v;  //num of vertises
    List* Array;
}Graph;

//Functions prototype--------------------------------------------
void load_File(graph G);
void print_graph(graph G);

//Heaps methods :
heap create_min_heap(int capacity);
int parent_node(int i);
int left_child(int i);
int right_child(int i);
void swap_nodes(heap H,int srcI,int desI) ;
void min_heapify(heap H, int i);
void enqueue(heap H, char src[], char des[], int distance);
HeapNode dequeue (heap H);
int IsEmptyHeap (heap H);

//graph functions :
graph create_graph(int v);
void Add_Edge(graph G, char cityA[], char cityB[], int distance);
Edge* create_Edge(char ciryA[],char cityB[],int distance);
int connected(graph g, int src, int dest, int visited[]);
int edge_exists(heap H,char src[],char dest[]);
int get_index(char city[]);
int Is_city_exist(char city[]);


//Primes function :
graph primes (graph G,char cityName[]);
//Kruskals Function:
graph Kruskals (graph G);



char Cities_name[100][30];  //cities
int count = 0;
HeapNode minh;
int main()
{
     graph MSTGragh=create_graph(100);
     graph KruskalsGraph=create_graph(100);
    //main menu :
    int option=0;
    char cityName[30];

    do{
            //main menu :
        printf("\nchoose an option :\n");
        printf("1- Load cities \n");
        printf("2- Apply Prims Algorithm\n");
        printf("3- Apply Kruskals Algorithm\n");
        printf("4- Compare the two algorithms\n");
        printf("5- Exist\n");
        printf("Enter your choice : ");
        scanf("%d",&option);
        switch(option){
        case 1 :
                 load_File(MSTGragh);  //loading file
                 print_graph(MSTGragh);        //printing the tree after loading
                 printf("Graph order = %d\n",count);
                 printf("Graph size = %d\n",count-1);
                 break;
        case 2 :
            printf("Enter the name of the city : \n");
            scanf("%s",&cityName);
           if(Is_city_exist(cityName)){  //check if thic name exist
              clock_t T1 ;  //finding the time for prims function
              T1=clock();
              MSTGragh=primes(MSTGragh,cityName);
              print_graph(MSTGragh);
              T1=clock()-T1;
            double time_taken = ((double)T1)/CLOCKS_PER_SEC;
            printf("prims took %f sec to execute \n",time_taken);
            }
           else printf("there is no such city :) \n");
            break;
        case 3 :{
            clock_t T2=clock();     //finding the time for Kruskals function
            KruskalsGraph=Kruskals(MSTGragh);
            print_graph(KruskalsGraph);
            T2=clock()-T2;
            double time_taken = ((double)T2)/CLOCKS_PER_SEC;
            printf("prims took %f sec to execute \n",time_taken);
            break;
        }
        case 4 :
            printf("for prims  ------------------------------------\n");
              clock_t T1 ;  //finding the time for prims function
              T1=clock();
              MSTGragh=primes(MSTGragh,MSTGragh->Array[0].head);
              T1=clock()-T1;
            double time_taken1 = ((double)T1)/CLOCKS_PER_SEC;
            printf("prims took %f sec to execute \n",time_taken1);

        printf("for Kruskal ------------------------------------\n");
           {
            clock_t T2=clock();     //finding the time for Kruskals function
            KruskalsGraph=Kruskals(MSTGragh);
            T2=clock()-T2;
            double time_taken2 = ((double)T2)/CLOCKS_PER_SEC;
            printf("Kruskal took %f sec to execute \n",time_taken2);
          }
            break;
        case 5 :
            printf("Exiting\n");
            free(MSTGragh->Array);
            free(KruskalsGraph->Array);
            free(MSTGragh);
            free(KruskalsGraph);
        break;
        default :    printf("Invalid option. Please choose between 1 and 5.\n");
    break;
    }
    }while(option!=5);


    return 0;
}
// To load from cities file and addes the info to the gaph
void load_File(graph G){
    FILE* input = fopen("cities.txt", "r");            //opening the file
    if(input == NULL){                                 //checking if opened
        printf("Can't open file...\n");
    }
    char city_A[100], city_B[100], line[250];
    int distance = 0;
    while(fgets(line, sizeof(line), input)){         //reading the file
        char* token = strtok(line, "#");  //cutting each line and add it to the graph
        strcpy(city_A, token);
        token = strtok(NULL, "#");
        strcpy(city_B, token);
        token = strtok(NULL, "#");
        distance = atoi(token);
        Add_Edge(G, city_A, city_B, distance); //adding the data
    }
    fclose(input); //closeing the file
}
// a method to print graph
void print_graph(graph G){
    if(G == NULL || G->v == 0){   //checking if the graph is empty
        printf("Graph is empty.\n");
        return;
    }
    int visited[GraphSize][GraphSize] = {0};        // To avoid printing the same edge twice
    for (int i = 0; i < G->v; i++) {
        Edge* e = G->Array[i].head;
        while (e != NULL) {
            int srcI = get_index(e->src);
            int destI = get_index(e->dest);
            if (visited[srcI][destI]==0 && visited[destI][srcI]==0) {                  //check because its undirected : src to des same as des to src(same edge)
                printf("From %s To %s : %d Km\n", e->src, e->dest, e->weight);
                visited[srcI][destI] = 1;
                visited[destI][srcI] = 1;              // Mark both directions as printed
            }
            e = e->next;
        }
    }
}
// a method to create a priorty queue(min heap)
heap create_min_heap(int capacity){
    heap H = (heap)malloc(sizeof(MinHeap));  //reserve a place in memory for the heap
    H->size = 0;
    H->capacity = capacity;
    H->HeapArray = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    return H;
}
// a function to find the parent of a min heap
int parent_node(int i){
    return i/2;
}
//a function to find the left child of a min heap
int left_child(int i){
    return 2*i;
}
//a function to find the right child of a min heap
int right_child(int i){
    return 2*i+1;
}
//swapping heap nodes (if there is smth wrong with the min heap)
void swap_nodes(heap H,int srcI,int desI) {
    HeapNode temp = H->HeapArray[srcI];
     H->HeapArray[srcI] =  H->HeapArray[desI];
    H->HeapArray[desI]=temp;
}
// a function to create a heap
void min_heapify(heap H, int i){
    int left = left_child(i);        //getting the left and right childrens
    int right = right_child(i);
    int smallest = i;

    if(left < H->size && H->HeapArray[left].distance < H->HeapArray[smallest].distance)
        smallest = left;
    if(right < H->size && H->HeapArray[right].distance < H->HeapArray[smallest].distance)
        smallest = right;
    if(smallest != i){
        swap_nodes(H,i,smallest);
        min_heapify(H, smallest);
    }
}
// a function to add to the min heap
void enqueue(heap H, char src[], char des[], int distance){
    if(H->size >= H->capacity){                 //checking if there is a space in the heap
        printf("Full heap\n");
        return;
    }
    H->HeapArray[H->size].distance = distance;  //filling the information
    strcpy(H->HeapArray[H->size].src_city, src);
    strcpy(H->HeapArray[H->size].dest_city, des);
    int i = H->size;
    H->size++;     //incrementing the size

    while(i > 0 && H->HeapArray[parent_node(i)].distance > H->HeapArray[i].distance){  //swap the edges until the min heap is correct (parent is greater than childrens)
        swap_nodes(H,i,parent_node(i));
        i = parent_node(i);
    }
}
//a function to delete and return the min edge(have min distance=root)from the min heap
HeapNode dequeue (heap H){
    if(H->size ==0)        //check if the heap is empty
        printf("empty heap \n");

    HeapNode h =H->HeapArray[0];       //reaching the root(min distance)
    H->HeapArray[0]=H->HeapArray[H->size-1];
    H->size--;
    min_heapify(H,0);  //to update on the heap after removeing the root
    return h;
}
//a function to create a graph using adjacency list
graph create_graph(int v){
    graph G = (graph)malloc(sizeof(struct Graph));   //reserve a place in memory for the graph
    G->v = v;
    G->Array = (List*)malloc(v * sizeof(List));      //reserve a place in memory for the array
    for(int i = 0; i < v; i++){
        G->Array[i].head = NULL;       //making each array of lists point to null
    }
    return G;
}
//a function to create an edge
Edge* create_Edge(char cityA[],char cityB[],int distance){
    Edge* e =(struct Edge*)malloc(sizeof(struct Edge));  //reserve a place in memory for the edge
    strcpy(e->src,cityA);                   //filling the info of this edge
    strcpy(e->dest,cityB);
    e->weight=distance;
    e->next=NULL;
    return e;
}
// a function to add an edge to a graph
void Add_Edge (graph G, char cityA[], char cityB[], int distance){
    if(!Is_city_exist(cityA)){                    //checking it the source city exist in the array of cities ,if not add it
        strcpy(Cities_name[count++], cityA);
    }
    if(!Is_city_exist(cityB)){                //checking it the destination city exist in the array of cities  ,if not add it
        strcpy(Cities_name[count++], cityB);
    }
    int find_source = -1;
    int find_destination = -1;

    find_source=get_index(cityA);    //finding these cities index
    find_destination=get_index(cityB);

    Edge* e = create_Edge(cityA,cityB,distance);   // creating an edge and adding it to the graph
    e->next = G->Array[find_source].head;
    G->Array[find_source].head = e;

    e = create_Edge(cityB, cityA, distance);      //adding the opiste because its undirected
    e->next = G->Array[find_destination].head;
    G->Array[find_destination].head = e;

}
// a function to check if the city is in the array of cities
int Is_city_exist(char city[]){
    for(int i = 0; i < count; i++){
        if(strcmp(city, Cities_name[i]) == 0 )
            return 1;
    }
    return 0;
}
// a function to check if the heap is empty
int IsEmptyHeap (heap H){
    return H->size==0;
}
// finding the MST using primes algorithem
graph primes (graph G,char cityName[]){
    if (G == NULL || G->v == 0){                 //checking if the graph is empty
       printf("empty graph \n");
         return NULL;
    }

    int visited[order] = {0};          //an array to check if we visited this city or not
    int totalCost = 0;

   int index = get_index(cityName);   //the src city is visited ,so we made it 1
    visited[index] = 1;

    heap H = create_min_heap(GraphSize);         //creating the new graph and the min heap
    graph newGraph =create_graph(G->v);

    Edge* e = G->Array[index].head;             //adding the first array of linked list(src) to the priorty queue
    while (e != NULL) {
        enqueue(H, e->src, e->dest, e->weight);
        e = e->next;
    }
    while (!IsEmptyHeap(H)) {
        HeapNode min = dequeue(H);                   //adding the edge that has the min cost to the tree
        int destIndex = get_index(min.dest_city);
        if (visited[destIndex]!=0)                              //check if we have visited this city before
            continue;
        Add_Edge(newGraph,min.src_city,min.dest_city,min.distance);    //if not add it to the graph
        totalCost += min.distance;
        visited[destIndex] = 1;           //make the city visited

        Edge* temp = G->Array[destIndex].head;       //adding the next city(des city) to the min heap
        while (temp != NULL) {
            enqueue(H, temp->src, temp->dest, temp->weight);
            temp = temp->next;
        }
    }
    free(H->HeapArray);   //deleting the heap
    free(H);
    printf("Total cost = %d\n", totalCost);
    return newGraph;
}

// finding the MST using Kruskals algorithem
graph Kruskals (graph G){
     if (G == NULL || G->v == 0) { //checking if the graph is empty
        printf("empty graph\n");
        return NULL;
     }

    int totalCost=0;
    heap H = create_min_heap(GraphSize); //creating a heap to find the minedge using it
    graph newGraph = create_graph(G->v); // the new graph that were going to store the Kruskals graph in it

    //splitting the graph int edges and store them in min heap

    for (int i = 0; i < count; i++) {
        Edge* e = G->Array[i].head;
        while (e != NULL) {
            if(!edge_exists(H,e->src,e->dest)){        // check if the edge exist to avoiding duplicate
                enqueue(H, e->src, e->dest, e->weight);
            }
            e = e->next;
        }
    }
    int a=0;
    while(!IsEmptyHeap(H) && a < G->v-1){
    HeapNode h = dequeue(H);  // extract the cheapest edge

    int srcI =get_index(h.src_city); //finding the src and des indes of the cheapest edge
    int desI =get_index(h.dest_city);

    int visitedC[GraphSize]={0};   //checking if there is a cycle
    if(!connected(newGraph,srcI,desI,visitedC)){ //if no add it to the graph
        Add_Edge(newGraph,h.src_city,h.dest_city,h.distance);
        a++;
      }
    }
    for(int j =0;j<newGraph->v;j++){    //calculating the total cost
            Edge* edg = newGraph->Array[j].head;
            while(edg!=NULL){
            totalCost+=edg->weight;
            edg=edg->next;
       }
    }
    totalCost/=2;
    printf("Total cost = %d\n", totalCost);
    free(H->HeapArray);  //free the min heap
    free(H);
    return newGraph;
}
// a function that finds the index of a city based on its name
int get_index(char city[]) {
    for (int i = 0; i < count; i++) { //finding the city
        if (strcmp(Cities_name[i], city) == 0)
            return i;
    }
    return -1; //because the array starts from 0
}
// a function to check if the city exist
int edge_exists(heap H,char src[],char dest[]) {
    for (int i = 0; i < H->size; i++) {  //because its undirected graph i have to check both src and des
        if ((strcmp(H->HeapArray[i].src_city, src) == 0 && strcmp(H->HeapArray[i].dest_city, dest) == 0) ||
            (strcmp(H->HeapArray[i].src_city, dest) == 0 && strcmp(H->HeapArray[i].dest_city, src) == 0)) {
            return 1; // edge already exists
        }
    }
    return 0;
}
// a function to check if there is a path between two cities to avoid duplicating the undiected graph
int connected(graph g, int src, int dest, int visited[]) {
    if (src == dest) return 1;
    visited[src] = 1;          //mark the src city visited
    Edge* e = g->Array[src].head;
    while (e != NULL) {
        int neighbor = get_index(e->dest);  //finding the src neighpor
        if (!visited[neighbor]) {
            if (connected(g, neighbor, dest, visited)) {
                return 1;
            }
        }
        e = e->next;
    }
    return 0;
}
