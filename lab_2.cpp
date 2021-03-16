#include <iostream>

#define SIZE 10

struct node
{
    int data{};
    node *next{nullptr};
};

class list_gr
{
private:
    node *head, *tail;

public:
    list_gr()
    {
        head = NULL;
        tail = NULL;
    }
    void create_node(int value);
    void display_node(node *tmp);
    void display_list();
    node *begin();
    void memory_clear();
    void display();
};

class stack_gr
{
    int *arr;
    int top;
    int capacity;

public:
    stack_gr(int size = SIZE)
    {
        arr = new int[size];
        capacity = size;
        top = -1;
    };
    ~stack_gr()
    {
        delete[] arr;
    };
    void push(int);
    int pop();
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
    void print();
    bool already_in_the_stack_gr(int data);
};

class queue_gr
{
    int front, rear, capacity;
    int *queue;

public:
    queue_gr(int c)
    {
        front = rear = 0;
        capacity = c;
        queue = new int[c];
    }
    ~queue_gr()
    {
        delete[] queue;
    }
    void add(int data);
    int remove();
    void queue_display();
    bool isEmpty_2();
    bool already_in_the_queue_gr(int data);
};

void display_graph(int, list_gr *arr);
void create_the_graph(list_gr *&arr, int &num_elem, bool *&visited);
void DFS_RECUR(list_gr *arr, int cur, bool *&visited, stack_gr &stk, int *&result, int &i);
void BFS_RECUR(list_gr *arr, int cur, bool *&visited, queue_gr &queue, int *&result, int &i);
void menu(int &choice, bool &inserted);
void display_result(int *result);
void result_clear(int num_elem, int *&result);
void visited_clear(bool* &visited, int num_elem);

int main()
{
    int num_elem, choice;
    list_gr *arr;
    bool *visited;
    int *result;
    bool inserted = false;
    while (choice != 5)
    {
        menu(choice, inserted);
        if (choice == 1)
        {
            if (inserted == true)
            {
                for (int i = 0; i < num_elem; ++i)
                {
                    arr[i].memory_clear();
                }
                arr = nullptr;
                delete[] result;
                result = nullptr;
            }
            create_the_graph(arr, num_elem, visited);
            display_graph(num_elem, arr);
            result = new int[num_elem + 1];
            result_clear(num_elem, result);
            inserted = true;
        }
        if (choice == 2)
        {
            stack_gr stk;
            int i = 0;
            DFS_RECUR(arr, 0, visited, stk, result, i);
        }
        if (choice == 3)
        {
            queue_gr queue(num_elem);
            int i = 0;
            BFS_RECUR(arr, 0, visited, queue, result, i);
        }
        if (choice == 4)
        {
            display_result(result);
            result_clear(num_elem, result);
            visited_clear(visited, num_elem);
        }
        if (choice == 5)
        {
            for(int i = 0; i < num_elem; ++i)
            {
                arr[i].memory_clear();
                arr = nullptr;
            }
            delete [] visited;
            visited = nullptr;
            delete [] result;
            visited = nullptr;
            std::cout << "Программа завершена";
        }
    }
}

node *list_gr::begin()
{
    return head;
}

void list_gr::create_node(int value)
{
    node *tmp = new node;
    tmp->data = value;
    tmp->next = NULL;
    if (head == NULL)
    {
        head = tmp;
        tail = tmp;
        tmp = NULL;
    }
    else
    {
        tail->next = tmp;
        tail = tmp;
    }
}

void list_gr::display_node(node *tmp)
{
    std::cout << tmp->data << "  ";
}

void list_gr::display_list()
{
    node *tmp = new node;
    tmp = head;
    while (tmp != nullptr)
    {
        display_node(tmp);
        tmp = tmp->next;
    }
}

void list_gr::display()
{
    std::cout << head <<"  "<< tail;
}

void create_the_graph(list_gr *&arr, int &num_elem, bool *&visited)
{
    std::cout << "Напишите количество вершин в графе - ";
    std::cin >> num_elem;
    arr = new list_gr[num_elem];
    visited = new bool[num_elem]{false};
    int digit;
    bool finish;
    std::cout << "Заполнить список смежности построчно ('-1', чтоб закончить заполнение строчки):"<<std::endl;
    for (int i = 0; i < num_elem; ++i)
    {
        std::cin >> digit;
        while (digit != -1)
        {
            arr[i].create_node(digit);
            std::cin >> digit;
        }
    }
}

void display_graph(int num_elem, list_gr *arr)
{
    for (int i = 0; i < num_elem; ++i)
    {
        std::cout << i << " - ";
        arr[i].display_list();
        std::cout << std::endl;
    }
}

void stack_gr::push(int x)
{
    if (isFull())
    {
        std::cout << "Overflow\nProgram Terminated\n";
        return;
    }
    //std::cout << "Inserting " << x << std::endl;
    arr[++top] = x;
}

int stack_gr::pop()
{
    if (isEmpty())
    {
        std::cout << "Underflow\nProgram Terminated\n";
        return -1;
    }

    //std::cout << "Removing " << peek() << std::endl;
    return arr[top--];
}

int stack_gr::peek()
{
    if (!isEmpty())
    {
        return arr[top];
    }
    else
    {
        return -1;
    }
}

int stack_gr::size()
{
    return top + 1;
}

bool stack_gr::isEmpty()
{
    return top == -1;
}

bool stack_gr::isFull()
{
    return top == capacity - 1;
}

void stack_gr::print()
{
    for (int i = 0; i < top + 1; ++i)
    {
        std::cout << ": ";
        std::cout << arr[i] << "\t";
    }
    std::cout << std::endl;
}

bool stack_gr::already_in_the_stack_gr(int data)
{
    for (int i = 0; i < top + 1; ++i)
    {
        if (arr[i] == data)
        {
            return true;
        }
    }
    return false;
}

void DFS_RECUR(list_gr *arr, int cur, bool *&visited, stack_gr &stk, int *&result, int &i)
{
    node *tmp = new node;
    result[i++] = cur;
    visited[cur] = true;
    tmp = arr[cur].begin();
    while (tmp != nullptr)
    {
        if (visited[tmp->data] != true && stk.already_in_the_stack_gr(tmp->data) != true)
        {
            stk.push(tmp->data);
        }
        tmp = tmp->next;
    }
    if (stk.isEmpty() != true)
    {
        DFS_RECUR(arr, stk.pop(), visited, stk, result, i);
    }
}

void queue_gr::add(int data)
{
    if (capacity == rear)
    {
        std::cout << "Queue is full\n";
        return;
    }
    else
    {
        queue[rear] = data;
        rear++;
    }
}

int queue_gr::remove()
{
    if (front == rear)
    {
        std::cout << "Queue is  empty\n";
        return -1;
    }
    else
    {
        int tmp = queue[0];
        for (int i = 0; i < rear - 1; i++)
        {
            queue[i] = queue[i + 1];
        }
        rear--;
        return tmp;
    }
}

void queue_gr::queue_display()
{
    int i;
    if (isEmpty_2())
    {
        std::cout << "Queue is Empty\n";
        return;
    }
    for (i = front; i < rear; i++)
    {
        std::cout << queue[i] << "<-- ";
    }
    return;
}

bool queue_gr::isEmpty_2()
{
    return front == rear;
}

bool queue_gr::already_in_the_queue_gr(int data)
{
    for (int i = 0; i < rear; ++i)
    {
        if (queue[i] == data)
        {
            return true;
        }
    }
    return false;
}

void BFS_RECUR(list_gr *arr, int cur, bool *&visited, queue_gr &queue, int *&result, int &i)
{
    node *tmp = new node;
    result[i++] = cur;
    visited[cur] = true;
    tmp = arr[cur].begin();
    while (tmp != nullptr)
    {
        if (visited[tmp->data] != true && queue.already_in_the_queue_gr(tmp->data) != true)
        {
            queue.add(tmp->data);
        }
        tmp = tmp->next;
    }
    if (queue.isEmpty_2() != true)
    {
        BFS_RECUR(arr, queue.remove(), visited, queue, result, i);
    }
}

void list_gr::memory_clear()
{
    if (head == tail)
    {
        head = nullptr;
        tail = nullptr;
        return;
    }
    node *cur = new node;
    node *prev = new node;
    prev = head;
    cur = prev->next;
    while (cur != NULL)
    {
        prev->next = nullptr;
        delete prev;
        prev = cur;
        cur = cur->next;
    }
    delete prev;
    head = nullptr;
    tail = nullptr;
}

void display_result(int *result)
{
    int i = 0;
    while (result[i] != -1)
    {
        std::cout << result[i] << "\t";
        i++;
    }
    std::cout << std::endl;
}

void menu(int &choice, bool &inserted)
{
    std::cout << "Меню:\n1.Ввод графа\n2.Обход введеного графа в глубину\n3.Обход введеного графа в ширину\n4.Выдача номеров пройденных вершни на дисплей\n5.Окончание программы" << std::endl;
    std::cin >> choice;
    while (choice < 0 || choice > 5)
    {
        std::cout << "Вы ввели невозможную цифру, попробуйте еще раз - ";
        std::cin >> choice;
    }
    while (inserted != true && choice != 1)
    {
        std::cout << "Для начала нужно ввести граф(для этого нажмите 1) - ";
        std::cin >> choice;
    }
}

void result_clear(int num_elem, int *&result)
{
    for (int i = 0; i < num_elem + 1; ++i)
    {
        result[i] = -1;
    }
}

void visited_clear(bool* &visited, int num_elem)
{
    for(int i = 0; i < num_elem; ++i)
    {
        visited[i] = false;
    }
}