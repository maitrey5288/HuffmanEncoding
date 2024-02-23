#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>

typedef struct Node {
	struct Node *left, *right;
	int freq;
	char c;
} *node;


int totalnodes = 0, qend = 1;
struct Node memory[256] = {{0}};
node qqq[255], *q = qqq-1;
char *code[128] = {0}, buf[1024];
int input_data=0,output_data=0;

node new_node(int freq, char c, node a, node b)
{
	node n = memory + totalnodes++;
	if (freq != 0){
		n->c = c;
		n->freq = freq;
	}
	else { 
		n->left = a, n->right = b;
		n->freq = a->freq + b->freq;
	}
	return n;
}


void qinsert(node n)
{
	int j, i = qend++;
	while ((j = i / 2)) {
		if (q[j]->freq <= n->freq) break;
		q[i] = q[j], i = j;
	}
	q[i] = n;
}

node qremove()
{
	int i, l;
	node n = q[i = 1];

	if (qend < 2) return 0;
	qend--;
	while ((l = i * 2) < qend) {
		if (l + 1 < qend && q[l + 1]->freq < q[l]->freq) l++;
		q[i] = q[l], i = l;
	}
	q[i] = q[qend];

	return n;
}

void build_code(node n, char *s, int len)
{
	static char *out = buf;
	if (n->c) {
		s[len] = 0;
		strcpy(out, s);
		code[(int)n->c] = out;
		out += strlen(s) + 1;
		return;
	}

	s[len] = '0'; build_code(n->left,  s, len + 1);
	s[len] = '1'; build_code(n->right, s, len + 1);
}

void importFile(FILE *fp_in, int *freq){
	char c,s[16]={0};
	int i = 0;

	while((c=fgetc(fp_in))!=EOF){
        freq[(int)c]++;
	}
	for (i = 0; i < 128; i++)
		if (freq[i]) qinsert(new_node(freq[i], i, 0, 0));

	while (qend > 2)
		qinsert(new_node(0, 0, qremove(), qremove()));

	build_code(q[1], s, 0);
}

void encode(FILE* fp_in, FILE* fp_out, int *freq ){

	char in,c,temp[20] = {0};
	int i,j=0,k=0,lim=0;
	rewind(fp_in);
	for(i=0; i<128; i++){
		if(freq[i])	lim += (freq[i]*strlen(code[i]));
	}
	output_data = lim;
	fprintf(fp_out,"%04d\n",lim);
	printf("\nEncoded:\n");
	for(i=0; i<lim; i++){
		if(temp[j] == '\0'){
			in = fgetc(fp_in);
			strcpy(temp,code[in]);
			printf("%s",code[in]);
			j = 0;
		}
		if(temp[j] == '1')
                        c = c|(1<<(7-k));
                else if(temp[j] == '0')
                        c = c|(0<<(7-k));
                else
                        printf("ERROR: Wrong input!\n");
                k++;
		j++;
		if(((i+1)%8 == 0) || (i==lim-1)){
                        k = 0;
                        fputc(c,fp_out);
                        c = 0;
                }
	}
	putchar('\n');
}

void print_code(int *freq){
	int i;
	printf("\n---------CODE TABLE---------\n----------------------------\nCHAR  FREQ  CODE\n----------------------------\n");
	for(i=0; i<128; i++){
		if(isprint((char)i)&&code[i]!=NULL&&i!=' ')
			printf("%-4c  %-4d  %16s\n",i,freq[i],code[i]);
		else if(code[i]!=NULL){
			switch(i){
				case '\n':
					printf("\\n  ");
					break;
				case ' ':
					printf("\' \' ");
					break;
				case '\t':
					printf("\\t  ");
					break;
				default:
					printf("%0X  ",(char)i);
					break;
			}
			printf("  %-4d  %16s\n",freq[i],code[i]);
		}
	}
	printf("----------------------------\n");

}

int main(int argc, char* argv[]){
	FILE *fp_in, *fp_out;
	char file_name[50]={"test.txt"};
	int freq[128] = {0},i;

	if((fp_in = fopen(file_name,"r"))==NULL){
		printf("\nERROR: No such file\n");
		return 0;
	}
	importFile(fp_in,freq);

	print_code(freq);

	encode(fp_in,fp_out,freq);

	fclose(fp_in);
	fclose(fp_out);

	return 0;
}
