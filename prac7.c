/*
 * Huffman Coding en C
 * 1) Carga un archivo de texto con al menos 50 palabras.
 * 2) Genera el diccionario de frecuencias de cada símbolo (byte) del archivo.
 * 3) Construye el árbol de Huffman.
 * 4) Genera los códigos de Huffman.
 * 5) Comprime el contenido y calcula tasa de compresión.
 * 6) Almacena el archivo codificado en "codificado.txt".
 * 7) Carga "codificado.txt" y decodifica usando el árbol, guardando en "decodificado.txt".
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 256

// Nodo de árbol Huffman
typedef struct Node {
    unsigned char ch;
    unsigned freq;
    struct Node *left, *right;
} Node;

// Min-heap para construir el árbol
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    Node** array;
} MinHeap;

Node* newNode(unsigned char ch, unsigned freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (Node**)malloc(capacity * sizeof(Node*));
    return heap;
}

void swapNode(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;
    if (left < heap->size && heap->array[left]->freq < heap->array[smallest]->freq)
        smallest = left;
    if (right < heap->size && heap->array[right]->freq < heap->array[smallest]->freq)
        smallest = right;
    if (smallest != idx) {
        swapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

int isSizeOne(MinHeap* heap) {
    return (heap->size == 1);
}

Node* extractMin(MinHeap* heap) {
    Node* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return temp;
}

void insertMinHeap(MinHeap* heap, Node* node) {
    heap->size++;
    int i = heap->size - 1;
    while (i && node->freq < heap->array[(i-1)/2]->freq) {
        heap->array[i] = heap->array[(i-1)/2];
        i = (i-1)/2;
    }
    heap->array[i] = node;
}

MinHeap* buildMinHeap(unsigned char symbols[], unsigned freqs[], unsigned n) {
    MinHeap* heap = createMinHeap(n);
    for (unsigned i = 0; i < n; ++i)
        heap->array[i] = newNode(symbols[i], freqs[i]);
    heap->size = n;
    int i = (heap->size - 1) / 2;
    for (; i >= 0; --i)
        minHeapify(heap, i);
    return heap;
}

Node* buildHuffmanTree(unsigned char symbols[], unsigned freqs[], unsigned n) {
    Node *left, *right, *top;
    MinHeap* heap = buildMinHeap(symbols, freqs, n);
    while (!isSizeOne(heap)) {
        left = extractMin(heap);
        right = extractMin(heap);
        top = newNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(heap, top);
    }
    Node* root = extractMin(heap);
    free(heap->array);
    free(heap);
    return root;
}

// Tabla de códigos: para cada símbolo guarda su código binario (string)
char* codes[MAX_SYMBOLS];
char arr[100];

void buildCodes(Node* root, int top) {
    if (root->left) {
        arr[top] = '0';
        buildCodes(root->left, top + 1);
    }
    if (root->right) {
        arr[top] = '1';
        buildCodes(root->right, top + 1);
    }
    if (!root->left && !root->right) {
        arr[top] = '\0';
        codes[root->ch] = (char*)malloc(top + 1);
        strcpy(codes[root->ch], arr);
    }
}

// Libera árbol
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    const char* filename = "input.txt";
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    // Contar frecuencias
    unsigned freqs[MAX_SYMBOLS] = {0};
    int c;
    unsigned original_bytes = 0;
    while ((c = fgetc(fp)) != EOF) {
        freqs[(unsigned char)c]++;
        original_bytes++;
    }
    if (original_bytes == 0) {
        fprintf(stderr, "Archivo vacío\n");
        fclose(fp);
        return 1;
    }

    // Construir lista de símbolos
    unsigned symbols_count = 0;
    unsigned char symbols[MAX_SYMBOLS];
    unsigned counts[MAX_SYMBOLS];
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (freqs[i] > 0) {
            symbols[symbols_count] = (unsigned char)i;
            counts[symbols_count] = freqs[i];
            symbols_count++;
        }
    }

    // Si solo un símbolo, manejar caso trivial
    if (symbols_count == 1) {
        codes[symbols[0]] = strdup("0");
    } else {
        Node* root = buildHuffmanTree(symbols, counts, symbols_count);
        buildCodes(root, 0);
        fclose(fp);

        // Codificar
        fp = fopen(filename, "rb");
        FILE* fout = fopen("codificado.txt", "w");
        if (!fout) { perror("fopen codificado"); return 1; }
        unsigned coded_bits = 0;
        while ((c = fgetc(fp)) != EOF) {
            char* code = codes[(unsigned char)c];
            fputs(code, fout);
            coded_bits += strlen(code);
        }
        fclose(fp);
        fclose(fout);

        // Reportar tasa de compresión
        unsigned original_bits = original_bytes * 8;
        printf("Bits original: %u\n", original_bits);
        printf("Bits codificado: %u\n", coded_bits);
        printf("Tasa de compresión: %.2f%%\n",
               100.0 * (1.0 - (double)coded_bits / original_bits));

        // Decodificar
        FILE* fin = fopen("codificado.txt", "r");
        FILE* fout2 = fopen("decodificado.txt", "w");
        if (!fin || !fout2) { perror("fopen decod"); return 1; }
        Node* node = buildHuffmanTree(symbols, counts, symbols_count);
        Node* curr = node;
        while ((c = fgetc(fin)) != EOF) {
            if (c == '0') curr = curr->left;
            else if (c == '1') curr = curr->right;
            if (!curr->left && !curr->right) {
                fputc(curr->ch, fout2);
                curr = node;
            }
        }
        fclose(fin);
        fclose(fout2);

        // Liberar memoria
        freeTree(root);
        freeTree(node);
    }

    // Liberar códigos
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (codes[i]) free(codes[i]);
    }
    return 0;
}
