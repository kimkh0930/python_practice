﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 10007
#define INPUT_SIZE 5000

typedef struct {
	int id;
	char name[20];
}Student;

typedef struct { //연결리스트로 들어가도록 bucket생성(하나의 키에 여러 데이터가 들어갈 수 있음을 의미)
	Student* data;
	struct Bucket* next;
}Bucket;

void init(Bucket** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable[i] = NULL;
	}
}
//해시 테이블 메모리 반환
void destructor(Bucket** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			free(hashTable[i]);
		}
	}
}

int isExist(Bucket** hashTable, int id) {
	int i = id % TABLE_SIZE;
	if (hashTable[i] == NULL)return 0; //존재하지 않으면 0
	else {
		Bucket* cur = hashTable[i];
		while (cur != NULL) {
			if (cur->data->id == id)return 1; //존재하면 1반환 
			cur = cur->next;
		}
	}
	return 0;
}

void add(Bucket** hashTable, Student* input) {
	int i = input->id % TABLE_SIZE;
	if (hashTable[i] == NULL) {
		hashTable[i] = (Bucket*)malloc(sizeof(Bucket));
		hashTable[i]->data = input;
		hashTable[i]->next = NULL;
	}
	else {
		Bucket* cur = (Bucket*)malloc(sizeof(Bucket));
		cur->data = input;
		cur->next = hashTable[i];
		hashTable[i] = cur;
	}
}

void show(Bucket** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			Bucket* cur = hashTable[i];
			while (cur != NULL) {
				printf("키: [%d] 이름: [%s]\n", i, cur->data->name);
				cur = cur->next;
			}
		}
	}
}

int main(void) {
	Bucket** hashTable;
	hashTable = (Bucket**)malloc(sizeof(Bucket) * TABLE_SIZE);
	init(hashTable);
	
	for (int i = 0; i < INPUT_SIZE; i++) {
		Student* student = (Student*)malloc(sizeof(Student));
		student->id = rand() % 1000000;
		sprintf(student->name, "사람%d", student->id);
		if (!isExist(hashTable, student->id)) {
			add(hashTable, student);
		}
	}

	show(hashTable);
	destructor(hashTable);
	system("pause");
	return 0;
}