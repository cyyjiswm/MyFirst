#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
	return document[n - 1][m - 1][k - 1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) {
	return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, int k) {
	return document[k - 1];
}

char**** get_document(char* text) {
	char *p = text;
	char **sen = (char**)malloc(sizeof(char*) * 100);
	char ***para = (char***)malloc(sizeof(char**) * 100);
	char ****Docu = (char****)malloc(sizeof(char***) * 100);
	sen[0] = p; para[0] = sen; Docu[0] = para;
	int m = 0, n = 0, i = 0, t = 0;
	int num = strlen(text);
	for (i = 0; i < num; i++)
	{
		if (p[i] == ' ')
		{
			p[i] = '\0';
			sen[++t] = p + i + 1;
		}
		if (p[i] == '.'&&p[i + 1] != '\n')
		{
			p[i] = '\0';
			sen[++t] = p + i + 1;
			para[++m] = sen + t;
		}
		if (p[i] == '\n')
		{
			p[i] = '\0';
			p[i - 1] = '\0';
			sen[++t] = p + i + 1;
			para[++m] = sen + t;
			Docu[++n] = para + m;
		}
	}
	return Docu;
}


char* get_input_text() {
	int paragraph_count;
	scanf("%d", &paragraph_count);

	char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
	memset(doc, 0, sizeof(doc));
	getchar();
	for (int i = 0; i < paragraph_count; i++) {
		scanf("%[^\n]%*c", p[i]);
		strcat(doc, p[i]);
		if (i != paragraph_count - 1)
			strcat(doc, "\n");
	}

	char* returnDoc = (char*)malloc((strlen(doc) + 1) * (sizeof(char)));
	strcpy(returnDoc, doc);
	return returnDoc;
}

void print_word(char* word) {
	printf("%s", word);
}

void print_sentence(char** sentence) {
	int word_count;
	scanf("%d", &word_count);
	for (int i = 0; i < word_count; i++){
		printf("%s", sentence[i]);
		if (i != word_count - 1)
			printf(" ");
	}
}

void print_paragraph(char*** paragraph) {
	int sentence_count;
	scanf("%d", &sentence_count);
	for (int i = 0; i < sentence_count; i++) {
		print_sentence(*(paragraph + i));
		printf(".");
	}
}

int main()
{
	char* text = get_input_text();
	char**** document = get_document(text);

	int q;
	scanf("%d", &q);

	while (q--) {
		int type;
		scanf("%d", &type);

		if (type == 3){
			int k, m, n;
			scanf("%d %d %d", &k, &m, &n);
			char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
			print_word(word);
		}

		else if (type == 2){
			int k, m;
			scanf("%d %d", &k, &m);
			char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
			print_sentence(sentence);
		}

		else{
			int k;
			scanf("%d", &k);
			char*** paragraph = kth_paragraph(document, k);
			print_paragraph(paragraph);
		}
		printf("\n");
	}
	free(document);
}