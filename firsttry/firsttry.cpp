#include "stdafx.h"
#include "firsttry.h"

#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <Windows.h>



#define BUTTONCONTROL_01 1
#define BUTTONCONTROL_02 2
#define BUTTONCONTROL_03 3


#define N 200

#define MAX_LOADSTRING 100

//simple linked list
struct node
{
	int data;
	struct node* next;
};

struct node* SortedMerge(struct node* a, struct node* b)
{
	struct node* result = NULL;

	/* Base cases */
	if (a == NULL)
		return(b);
	else if (b == NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (a->data <= b->data)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return(result);
}

void FrontBackSplit(struct node* source, struct node** frontRef, struct node** backRef)
{
	struct node* fast;
	struct node* slow;
	if (source == NULL || source->next == NULL)
	{
		/* length < 2 cases */
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		/* Advance 'fast' two nodes, and advance 'slow' one node */
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		/* 'slow' is before the midpoint in the list, so split it in two
		at that point. */
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

void MergeSort(struct node** headRef)
{
	struct node* head = *headRef;
	struct node* a;
	struct node* b;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}

void push(struct node** head_ref, int new_data)
{
	/* allocate node */
	struct node* new_node =
		(struct node*) malloc(sizeof(struct node));

	/* put in the data  */
	new_node->data = new_data;

	/* link the old list off the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

//end simple linked list

//vector
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int *L, *R;
	L = (int*)malloc(n1*sizeof(int));
	R = (int*)malloc(n2*sizeof(int));


	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
	else
		return;
}

//end vector

//dubly linked list
struct nod
{
	int data;
	struct nod *next, *prev;
};

struct nod *split(struct nod *head)
{
	struct nod *fast = head, *slow = head;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	struct nod *temp = slow->next;
	slow->next = NULL;
	return temp;
}

struct nod *Merge(struct nod *first, struct nod *second)
{
	// If first linked list is empty
	if (!first)
		return second;

	// If second linked list is empty
	if (!second)
		return first;

	// Pick the smaller value
	if (first->data < second->data)
	{
		first->next = Merge(first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return first;
	}
	else
	{
		second->next = Merge(first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return second;
	}
}

struct nod *mergesort(struct nod *head)
{
	if (!head || !head->next)
		return head;
	struct nod *second = split(head);

	// Recur for left and right halves
	head = mergesort(head);
	second = mergesort(second);

	// Merge the two sorted halves
	return Merge(head, second);
}

void insert(struct nod **head, int data)
{
	struct nod *temp =
		(struct nod *)malloc(sizeof(struct nod));
	temp->data = data;
	temp->next = temp->prev = NULL;
	if (!(*head))
		(*head) = temp;
	else
	{
		temp->next = *head;
		(*head)->prev = temp;
		(*head) = temp;
	}
}
//end dubly linked list


float maxim(float *a)
{
	int i;
	float max = 0;
	for (i = 0; i < N; i++)
		if (a[i]>max)
			max = a[i];
	return max;
}

float timp_ex_vector()
{
	int a[N];
	float v[N];
	int i, aux = 0;
	float ts, to;
	int nr_elem = 1;
	//float matrice_timp[N][2];

	while (nr_elem < N)
	{
		ts = clock();
		srand(time(NULL));
		for (i = 0; i < nr_elem + 1; i++)
			a[i] = rand();
		for (i = 0; i < nr_elem; i++)
			for (int j = i + 1; j<nr_elem + 1; j++)
				if (a[j]>a[i])
				{
				aux = a[j];
				a[j] = a[i];
				a[i] = a[j];
				}

		mergeSort(a, 0, nr_elem);

		to = clock();

		//matrice_timp[nr_elem][0] = (float)nr_elem;
		//matrice_timp[nr_elem][1] = (to - ts) / CLOCKS_PER_SEC * 1000;
		v[nr_elem] = (to - ts) / CLOCKS_PER_SEC;

		nr_elem++;
	}
	/*for (int k = 0; k < N; k++)
		v[k] = matrice_timp[k][1];*/
	float max_timp = maxim(v);

	return max_timp;
}

float timp_ex_lista_simplu()
{
	struct node* res = NULL;
	struct node* a = NULL;

	float v_timp[N];
	int i, aux = 0;
	float ts, to;
	int nr_elem = 1;
	
	while (nr_elem<N)
	{
		ts = clock();
		srand(time(NULL));
		for (i = 0; i<nr_elem; i++)
		{
			aux = rand();
			push(&a, aux);
		}

		MergeSort(&a);

		to = clock();
		v_timp[nr_elem - 1] = (to - ts) / CLOCKS_PER_SEC;

		res = NULL;
		a = NULL;
		nr_elem++;
	}

	return maxim(v_timp);
}

float timp_ex_lista_dublu()
{
	struct nod *head = NULL;

	float v_timp[N];
	int i, aux = 0;
	float ts, to;
	int nr_elem = 1;

	while (nr_elem < N)
	{
		ts = clock();
		srand(time(NULL));
		for (i = 0; i < nr_elem; i++)
		{
			aux = rand();
			insert(&head, aux);
		}

		head = mergesort(head);

		to = clock();
		v_timp[nr_elem - 1] = (to - ts) / CLOCKS_PER_SEC;

		head = NULL;
		nr_elem++;
	}

	return maxim(v_timp);
}




// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FIRSTTRY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIRSTTRY));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIRSTTRY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+6);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_FIRSTTRY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

	   hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
						   szWindowClass,
						   L"Tabela grafic",
						   WS_EX_PALETTEWINDOW,
						   CW_USEDEFAULT, CW_USEDEFAULT, 700, 335, 
						   NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//



BOOL verifica_vector = FALSE;
BOOL verifica_lista_simplu = FALSE;
BOOL verifica_lista_dublu = FALSE;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
	{
		
		//UP BUTTON
		LPCWSTR BUTTON_ID = L"BUTTON";
		LPCWSTR BUTTON_text = L"Sortare pe vector de numere";
		CreateWindowEx(NULL, BUTTON_ID, BUTTON_text, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 10, 45, 250, 30, hWnd, (HMENU)BUTTONCONTROL_01, NULL, NULL);
		//End UP BUTTON

		//MIDDLE BUTTON
		LPCWSTR BUTTON_ID1 = L"BUTTON";
		LPCWSTR BUTTON_text1 = L"Sortare pe lista simplu inlantuita";
		CreateWindowEx(NULL, BUTTON_ID1, BUTTON_text1, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 10, 100, 250, 30, hWnd, (HMENU)BUTTONCONTROL_02, NULL, NULL);
		//End MIDDLE BUTTON

		//DOWN BUTTON
		LPCWSTR BUTTON_ID2 = L"BUTTON";
		LPCWSTR BUTTON_text2 = L"Sortare pe lista dublu inlantuita";
		CreateWindowEx(NULL, BUTTON_ID2, BUTTON_text2, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 10, 155, 250, 30, hWnd, (HMENU)BUTTONCONTROL_03, NULL, NULL);
		//End DOWN BUTTON

		//EXIT BUTTON
		LPCWSTR BUTTON_ID3 = L"BUTTON";
		LPCWSTR BUTTON_text3 = L"EXIT";
		CreateWindowEx(NULL, BUTTON_ID3, BUTTON_text3, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 10, 210, 250, 30, hWnd, (HMENU)IDM_EXIT, NULL, NULL);
		//End EXIT BUTTON
		

	}


	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case BUTTONCONTROL_01:
			verifica_vector = TRUE;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case BUTTONCONTROL_02:
			verifica_lista_simplu = TRUE;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case BUTTONCONTROL_03:
			verifica_lista_dublu = TRUE;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		TextOut(hdc, 150, 10, L"Aici se vor desena grafice", sizeof("Aici se vor desena grafice")-1);
		TextOut(hdc, 327, 25, L"timp(s*10^5)", sizeof("timp(s*10^5)") - 1);
		TextOut(hdc, 545, 230, L"numarul de", sizeof("numarul de") - 1);
		TextOut(hdc, 555, 245, L"numere", sizeof("numere") - 1);

		HPEN cont;
		HPEN contur;

		contur = CreatePen(PS_SOLID, 5, NULL);
		cont = (HPEN)SelectObject(hdc, contur);

		//creeare liniilor graficului
		MoveToEx(hdc, 340, 250, NULL);
		LineTo(hdc, 340, 45);
		MoveToEx(hdc, 340, 250, NULL);
		LineTo(hdc, 545, 250);

		//creearea sagetilor din capatul liniilor
		MoveToEx(hdc, 340, 45, NULL);
		LineTo(hdc, 335, 50);
		MoveToEx(hdc, 340, 45, NULL);
		LineTo(hdc, 345, 50);
		MoveToEx(hdc, 545, 250, NULL);
		LineTo(hdc, 540, 245);
		MoveToEx(hdc, 545, 250, NULL);
		LineTo(hdc, 540, 255);


		SelectObject(hdc, cont);
		DeleteObject(contur);

		//desenare grafic pe vector
		if (verifica_vector==TRUE)
		{
			HPEN hLinePen;
			HPEN hPenOld;
			float inalt1 = 0;
			float yPoz1 = timp_ex_vector()*100000;
			if (yPoz1 > 205)
				inalt1 = 205;
			else
				inalt1 = 250 - yPoz1;

			COLORREF qColor = RGB(0, 0, 200);
			hLinePen = CreatePen(PS_SOLID, 3, qColor);
			hPenOld = (HPEN)SelectObject(hdc, hLinePen);

			MoveToEx(hdc, 343, 248, NULL);
			LineTo(hdc, 545, inalt1);


			SelectObject(hdc, hPenOld);
			DeleteObject(hLinePen);
		}

		//desenare grafic pe lista simplu inlantuita
		if (verifica_lista_simplu==TRUE)
		{
			HPEN g_simplu;
			HPEN g_simplu_old;

			float inalt2 = 0;
			float yPoz2 = timp_ex_lista_simplu()*100000;
			if (yPoz2 > 205)
				inalt2 = 205;
			else
				inalt2 = 250 - yPoz2;

			COLORREF qColor = RGB(0, 200, 0);
			g_simplu = CreatePen(PS_SOLID, 3, qColor);
			g_simplu_old = (HPEN)SelectObject(hdc, g_simplu);

			MoveToEx(hdc, 343, 248, NULL);
			LineTo(hdc, 545, inalt2-10);

			SelectObject(hdc, g_simplu_old);
			DeleteObject(g_simplu);
		}

		//desenare grafic pe lista dublu inlantuita
		if (verifica_lista_dublu == TRUE)
		{
			HPEN g_dublu;
			HPEN g_dublu_old;
			float inalt3 = 0;
			float yPoz3 = timp_ex_lista_dublu() * 100000;
			if (yPoz3 > 205)
				inalt3 = 205;
			else
				inalt3 = 250 - yPoz3;

			COLORREF qColor = RGB(200, 0, 0);
			g_dublu = CreatePen(PS_SOLID, 3, qColor);
			g_dublu_old = (HPEN)SelectObject(hdc, g_dublu);

			MoveToEx(hdc, 343, 248, NULL);
			LineTo(hdc, 545, inalt3-20);

			SelectObject(hdc, g_dublu_old);
			DeleteObject(g_dublu);
		}


		

		EndPaint(hWnd, &ps);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
