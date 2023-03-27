#include <stdio.h>
#include <stdlib.h>

typedef struct Node { // Структура данных узла
    int key;
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *initNode(int key, int value) { // Функция инициализации узла
    Node *node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->value = value;
    return node;
}

void insertNode(Node *node, int key, int value) { // Вставка узла в дерево
    if (key < node->key) { // Если исходный ключ меньше текущего, то проверяем левого ребенка
        if (node->left == NULL) // Если он NULL, то вставляем на его место новый узел
            node->left = initNode(key, value);
        else insertNode(node->left, key, value); // Если он не NULL, то идём влево
    } else { // Если исходный ключ больше текущего, то проверяем правого ребенка
        if (node->right == NULL) // Если он NULL, то вставляем на его место новый узел
            node->right = initNode(key, value);
        else insertNode(node->right, key, value); // Если он не NULL, то идём вправо
    }
}

Node *searchNode(Node *node, int key) { // Поиск узла по ключу
    if (node == NULL) return NULL; // Если узел NULL вернем NULL
    if (node->key == key) return node; // Если ключ совпадает с искомым, то вернем узел
    if (key < node->key) // Если ключ исходный меньше текущего, то идём влево
        return searchNode(node->left, key);
    else // Иначе идём вправо
        return searchNode(node->right, key);
}

Node *getMin(Node *node) { // Поиск минимального узда
    if (node == NULL) return NULL; // Если узел NULL вернем NULL
    if (node->left == NULL) return node; // Если нет левого ребёнка, то узел минимальный, вернём его
    return getMin(node->left); // Иначе продолжаем идти влево
}

Node *getMax(Node *node) { // Поиск максимального узла
    if (node == NULL) return NULL; // Если узел NULL вернем NULL
    if (node->right == NULL) return node; // Если нет правого ребёнка, то узел максимальный, вернём его
    return getMax(node->right); // Иначе продолжаем идти вправо
}

Node *deleteNode(Node *node, int key) { // Удаление узла по ключу
    if (node == NULL) return NULL; // Если узел NULL вернем NULL
    else if (key < node->key) node->left = deleteNode(node->left, key); // Если ключ меньше текущего узла, то идём влево
    else if (key > node->key) node->right = deleteNode(node->right, key); // Если ключ больше текущего узла, то идём вправо
    else { // Случай когда мы наши узел, ключ которого равен искомому
        if (node->left == NULL || node->right == NULL) // Если один из детей NULL, то
            node = (node->left == NULL) ? node->right : node->left; // проверим NULL ли левый, если да то запишем правый, иначе наоборот
        else { // Если оба ребенка не NULL, то на место узла придет узел, который больше чем вся левая подветка и меньше чем вся правая, относительно удаляемого
            Node *temp_max_in_left = getMax(node->left); // запишем в переменную максимального из детей слева
            node->key = temp_max_in_left->key; // Перезапишем данные удаляемого узла
            node->value = temp_max_in_left->value;
            node->right = deleteNode(node->right, temp_max_in_left->key); // Удаляем узел, перешедший на место удаляемого из его старой позиции
        }
    }
    return node;
}

void printTree(Node *node) { // Симметричный обход (в порядке возрастания ключей)
    if (node == NULL) return;
    printTree(node->left);
    printf("Node key: %d, Node value: %d\n", node->key, node->value);
    printTree(node->right);
}

void deleteTree(Node *node) { // Обратный обход дерева (вывод: левый -> правый -> родитель) Применяется для очистки дерева из памяти
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    printf("Node key: %d, Node value: %d\n", node->key, node->value);
    free(node);
}

void copyTree(Node *node) { // Прямой обход дерева (вывод: родитель -> левый -> правый) Применяется копирования деревьев
    if (node == NULL) return;
    copyTree(node->left);
    copyTree(node->right);
    printf("Node key: %d, Node value: %d\n", node->key, node->value);
}

int main() {
    Node *root = initNode(10, 10);

    for (int i = 0; i < 6; ++i) {
        insertNode(root, i, i);
    }

    for (int i = 15; i < 20; ++i) {
        insertNode(root, i, i);
    }

    printTree(root);
    //copyTree(node);
    puts("!###DELETING TREE###!");
    deleteTree(root);
    return 0;
}
