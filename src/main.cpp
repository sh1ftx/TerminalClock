/*

* Por Kayki Ivan:

! Alterações e Adições:
1. Adicionada a função `setColor` para 
definir a cor do relógio com base no segundo 
atual.
2. Adicionada a função `resetColor` para 
resetar a cor para o padrão.
3. Adicionada a exibição dos números das 
horas no relógio.
4. Adicionada a exibição do horário em texto 
abaixo do relógio.
5. Adicionadas divisórias para organizar a 
visualização da saída.
*/


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <thread>
#include <chrono>

#define PI 3.14159265358979323846
#define RADIUS 20

// Função para converter graus para radianos
float degToRad(float degrees) {
	return degrees * (PI / 180);
}

// Função para traçar linhas de ponteiros (algoritmo de Bresenham adaptado para o terminal)
void drawLine(int x0, int y0, int x1, int y1, std::string endSymbol, std::string fillSymbol, std::string clock[2 * RADIUS + 1][2 * RADIUS + 1]) {
	int dx = abs(x1 - x0), dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	bool isEnd = false;
	while (true) {
    	if (x0 >= 0 && x0 < 2 * RADIUS + 1 && y0 >= 0 && y0 < 2 * RADIUS + 1) {
        	clock[y0][x0] = isEnd ? endSymbol : fillSymbol;
    	}
    	if (x0 == x1 && y0 == y1) {
        	isEnd = true;
    	}
    	if (isEnd) break;
    	int e2 = 2 * err;
    	if (e2 > -dy) { err -= dy; x0 += sx; }
    	if (e2 < dx) { err += dx; y0 += sy; }
	}
}

// Função para desenhar o relógio no terminal
void drawClock(int hour, int minute, int second) {
	std::string clock[2 * RADIUS + 1][2 * RADIUS + 1];

	// Limpar a matriz do relógio
	for (int i = 0; i < 2 * RADIUS + 1; ++i) {
    	for (int j = 0; j < 2 * RADIUS + 1; ++j) {
        	clock[i][j] = " ";
    	}
	}

	// Desenhar o círculo do relógio
	for (int angle = 0; angle < 360; angle += 6) {
    	int x = RADIUS + static_cast<int>(RADIUS * cos(degToRad(angle)));
    	int y = RADIUS - static_cast<int>(RADIUS * sin(degToRad(angle))); // Coordenada Y invertida
    	clock[y][x] = "*";
	}

	// Adicionar números das horas
	for (int hourMark = 1; hourMark <= 12; ++hourMark) {
    	int angle = 90 - 30 * hourMark;
    	int x = RADIUS + static_cast<int>((RADIUS - 2) * cos(degToRad(angle)));
    	int y = RADIUS - static_cast<int>((RADIUS - 2) * sin(degToRad(angle)));
    	clock[y][x] = std::to_string(hourMark);
	}

	// Calcular as posições dos ponteiros
	int secX = RADIUS + static_cast<int>((RADIUS - 1) * cos(degToRad(90 - 6 * second)));
	int secY = RADIUS - static_cast<int>((RADIUS - 1) * sin(degToRad(90 - 6 * second)));
	int minX = RADIUS + static_cast<int>((RADIUS - 2) * cos(degToRad(90 - 6 * minute)));
	int minY = RADIUS - static_cast<int>((RADIUS - 2) * sin(degToRad(90 - 6 * minute)));
	int hourX = RADIUS + static_cast<int>((RADIUS - 4) * cos(degToRad(90 - 30 * (hour % 12) - minute / 2.0)));
	int hourY = RADIUS - static_cast<int>((RADIUS - 4) * sin(degToRad(90 - 30 * (hour % 12) - minute / 2.0)));

	// Desenhar os ponteiros
	drawLine(RADIUS, RADIUS, secX, secY, "s", "s", clock); // Ponteiro de segundos
	drawLine(RADIUS, RADIUS, minX, minY, "m", "m", clock); // Ponteiro de minutos
	drawLine(RADIUS, RADIUS, hourX, hourY, "h", "h", clock); // Ponteiro de horas

	// Renderizar o relógio
	for (int i = 0; i < 2 * RADIUS + 1; ++i) {
    	for (int j = 0; j < 2 * RADIUS + 1; ++j) {
        	std::cout << clock[i][j];
    	}
    	std::cout << "\n";
	}
}

// Função para ajustar o heap
void AjustaHeap(std::vector<int>& arr, int n, int i) {
	int largest = i;    	// Inicializa o maior como a raiz
	int left = 2 * i + 1;   // Filho esquerdo
	int right = 2 * i + 2;  // Filho direito

	// Verifica se o filho esquerdo é maior que a raiz
	if (left < n && arr[left] > arr[largest])
    	largest = left;

	// Verifica se o filho direito é maior que o maior atual
	if (right < n && arr[right] > arr[largest])
    	largest = right;

	// Se o maior não for a raiz
	if (largest != i) {
    	std::swap(arr[i], arr[largest]);  // Troca os elementos

    	// Ajusta recursivamente o heap afetado
    	AjustaHeap(arr, n, largest);
	}
}

// Função principal do Heap Sort
void HeapSort(std::vector<int>& arr) {
	int n = arr.size();

	// Constrói o heap máximo
	for (int i = n / 2 - 1; i >= 0; i--)
    	AjustaHeap(arr, n, i);

	// Extrai os elementos do heap um por um
	for (int i = n - 1; i > 0; i--) {
    	std::swap(arr[0], arr[i]);  // Move o maior elemento para o final
    	AjustaHeap(arr, i, 0);    	// Ajusta o heap novamente
	}
}

// Função para exibir o array
void PrintArray(const std::vector<int>& arr) {
	for (int val : arr)
    	std::cout << val << " ";
	std::cout << std::endl;
}

void My_Sort(std::vector<int>& arr, bool descent = false)
{
	int n = arr.size();
	int aux = 0;
    
	for (int i = 0; i < n; i++)
	{
    	for (int j = 0; j < n; j++)
    	{
        	if (descent)
        	{
            	if (arr[i] > arr[j])
            	{
                	aux = arr[i];
                	arr[i] = arr[j];
                	arr[j] = aux;
            	}
        	}
        	else
        	{
            	if (arr[i] < arr[j])
            	{
                	aux = arr[i];
                	arr[i] = arr[j];
                	arr[j] = aux;
            	}
        	}
    	}
	}
}

void setColor(int second) {
	// Definir cor com base no segundo atual
	int colorCode = 31 + (second % 7); // Códigos de cores ANSI de 31 a 37
	std::cout << "\033[" << colorCode << "m";
}

void resetColor() {
	// Resetar cor para padrão
	std::cout << "\033[0m";
}

int main() {
	std::srand(std::time(0));

	int tamanho = 20;
	int limiteInferior = 1;
	int limiteSuperior = 100;
	std::vector<std::vector<int>> matriz(tamanho, std::vector<int>(tamanho, 0));
	int pares = 0;
	int impares = 0;

	for (int linha = 0; linha < tamanho; linha++) {
    	for (int coluna = 0; coluna < tamanho; coluna++) {
        	matriz[linha][coluna] = limiteInferior + std::rand() % (limiteSuperior - limiteInferior + 1);
    	}
	}

	for (int linha = 0; linha < tamanho; linha++) {
    	for (int coluna = 0; coluna < tamanho; coluna++) {
        	std::cout << matriz[linha][coluna] << "\t";
    	}
    	std::cout << "\n";
	}

	std::cout << "\n";

	while (true) {
    	// Obter o horário atual
    	std::time_t now = std::time(nullptr);
    	std::tm* timeInfo = std::localtime(&now);

    	int hour = timeInfo->tm_hour;
    	int minute = timeInfo->tm_min;
    	int second = timeInfo->tm_sec;

    	// Limpar a tela
#ifdef __unix__
    	system("clear"); // Use "clear" no linux
#else
    	system("cls"); // Use "cls" no Windows
#endif // __unix__

    	// Definir cor com base no segundo atual
    	setColor(second);

    	// Desenhar o relógio
    	std::cout << "=====================\n";
    	drawClock(hour, minute, second);
    	std::cout << "=====================\n";

    	// Resetar cor para padrão
    	resetColor();

    	// Exibir o horário em texto
    	std::cout << "Hora atual: " << hour << ":" << minute << ":" << second << "\n";

    	// Pausar por 1 segundo
    	std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}