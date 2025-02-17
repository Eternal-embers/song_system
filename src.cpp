#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define line printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n")
#define song_info "data\\song_info.txt"
#define help_file "data\\help.txt"
#define orgin_c "data\\src.txt"
#define backup "data\\song_backup.txt"
#define LEN1 40
#define LEN2 30
struct song{
	char name[LEN1];//歌曲名称
	char singer[LEN2];//歌手名称
	char type[30];//歌曲类别
	char date[40];//专辑
	struct song *next;
}sg;

//用于打印歌曲信息前的信息类别
const char *_song = "歌曲名称";
const char *_singer = "歌手名称";
const char *_company = "歌曲类别";
const char *_date = "专辑";

//菜单选项，用于与所输入的选项映射
const char order[15][10]={"exit","input","print","change","delete","search",
"save","print_f","change_f","delete_f","search_f","sort_f","backup","help","scheme"};

void menu(void){
	printf("    ________________________________________________\n");
	printf("    |>>>>>>>>>>>>>> 歌曲信息管理系统 <<<<<<<<<<<<<<|\n\n");
	printf("    exit- - - - - - - - - -退出\n\n");
	printf("    input- - - - - - - - - 输入\n\n");
	printf("    print- - - - - - - - - 打印所输入中的数据\n\n");
	printf("    change- - - - - - - - -修改所输入中的数据\n\n");
	printf("    delete- - - - - - - - -删除所输入中的数据\n\n");
	printf("    search- - - - - - - - -在所输入的数据中查询\n\n");
	printf("    save- - - - - - - - - -保存所输入的数据到文件中\n\n");
	printf("    print_f- - - - - - - - 打印已保存的歌曲信息\n\n");
	printf("    change_f- - - - - - - -修改已保存的歌曲信息\n\n");
	printf("    delete_f- - - - - - - -删除已保存的歌曲信息\n\n");
	printf("    search_f- - - - - - - -查询已保存的歌曲信息\n\n");
	printf("    sort_f- - - - -- - - - 排序已保存到歌曲信息\n\n");
	printf("    backup- - - - - - - - -备份已保存的歌曲信息\n\n");
	printf("    help- - - - - - - - - -帮助信息\n\n");
	printf("    scheme- - - - - - - - -设置主题\n\n");
	printf("    >>");
}

struct song *createhead(void){
	struct song *head;
	head = (struct song *)malloc(sizeof(struct song));
	strcpy(head->name,"head");
	strcpy(head->singer,"劣等生");
	strcpy(head->type,"理工");
	strcpy(head->date,"2022/2/13");
	return head;
}

struct song *input(void){
	line;
	int n,i;
	struct song *head,*p1,*p2;
	head = createhead();//特别插入一个头结点,方便删除结点
	p1 = (struct song *)malloc(sizeof(struct song));
	head->next = p1;
	printf("请输入要输入的数据组数(如果组数为负数,则结束输入)：\n>>");
	scanf("%d",&n);
	if(n<0) return NULL;
	printf("%-40s %-30s %-30s %-40s\n",_song,_singer,_company,_date);
	for(i = 0;i<n;i++){
	scanf("%s%s%s%s",p1->name,p1->singer,p1->type,p1->date);
	p2 = p1;
	p1 = (struct song *)malloc(sizeof(struct song));
	p2->next = p1;
	}
	p2->next = NULL;
	free(p1);
	line;
	return head;
}

void print(struct song *p){
	if(p==NULL) {
		printf("\t\t您尚未输入数据!");
		return;
	}
	line;
	p = p->next;//首结点无数据所以从第二个结点开始
	printf("%40s %30s %30s %40s\n\n",_song,_singer,_company,_date);
	while(p){
		printf("%40s %30s %30s %40s\n\n",p->name,p->singer,p->type,p->date);
		p = p->next;
	}
	line;
}

void change(struct song *p){
	if(p==NULL){
		printf("\t\t您尚未输入数据!");
		return;
	}
	line;
	char s[30];
	struct song *head = p;
	printf("请输入要修改的歌曲名(#结束修改)\n>>");
	scanf("%s",s);
	while(s[0]!='#'){
		p = head->next;
		while(p){
			if(strcmp(s,p->name)==0) break;
			p = p->next;
		}
		if(p!=NULL){
			printf("%s->",p->name);
			scanf("%s",p->name);
			printf("%s->",p->singer);
			scanf("%s",p->singer);
			printf("%s->",p->type);
			scanf("%s",p->type);
			printf("%s->",p->date);
			scanf("%s",p->date);
		}
			else printf("输入的歌曲信息中无\"%s\"此歌曲!\n",s);
		line;
		printf("请输入要修改的歌曲名(#结束修改)\n>>");
		scanf("%s",s);
	}
	line;
}

void dele(struct song *p){
	if(p==NULL) {
		printf("\t\t您尚未输入数据!");
		return;
	}
	line;
	struct song *pre,*head;
	head = p;
	char s[30];
	printf("请输入要删除的歌曲名\n>>");
	scanf("%s",s);
	while(s[0]!='#'){
		pre = head;
		p = head->next;
		while(p){
			if(strcmp(s,p->name)==0) break;
				p = p->next;
				pre = pre->next;
		}
		if(p!=NULL){
			pre->next = p->next;
			free(p);
			printf("- - - - - - - - -删除成功- - - - - - - - -\n");
		}
			else printf("输入的歌曲信息中无\"%s\"此歌曲的信息!\n",s);
		printf("请输入要删除的歌曲名\n>>");
		scanf("%s",s);
 	}
	line;
}

void search(struct song *p){
	if(p==NULL) {
		printf("\t\t您尚未输入数据!");
		return;
	}
	line;
	char s[30];
	struct song *head;
	head = p;
	printf("请输入要查询的歌曲名(#结束查询)\n>>");
	scanf("%s",s);
	while(s[0]!='#'){
		p = head->next;
		while(p){
			if(strcmp(s,p->name)==0) break;
			p = p->next;
		}
		if(p!=NULL) {
 			printf("%-40s %-30s %-30s %-40s\n",_song,_singer,_company,_date);
			printf("%-40s %-30s %-30s %-40s\n",p->name,p->singer,p->type,p->date);
		}
			else printf("输入的歌曲中无\"%s\"此歌曲!\n",s);
		printf("请输入要查询的歌曲名\n>>");
		scanf("%s",s);
	}
	line;
}

void save(struct song *p){
	if(p==NULL) {
		printf("\t\t无数据可保存！");
		return;
	}
	line;
	FILE *fp;
	struct song *head,*pt;
	head = p;
	p = p->next;
	fp = fopen(song_info,"a");
	while(p){
		fprintf(fp,"%40s %30s %30s %40s\n",p->name,p->singer,p->type,p->date);
		printf("%-40s %-30s %-30s %-40s\n",p->name,p->singer,p->type,p->date);
		p = p->next;
	}
	//fprintf(fp,"%40s %30s %30s %10s\n","#","#","#","#");
	printf("- - - - - - - -保存所输入的数据成功!- - - - - - - -\n");
	while(head){
		pt = head;
		head = head->next;
		free(pt);
	}//清理存储到链表中的数据
	fclose(fp);
	line;
}

void save_f(struct song *p){
	if(p==NULL) return;
	line;
	FILE *fp;
	struct song *head,*pt;
	head = &(*p);
	fp = fopen(song_info,"w");
	system("pause>NULL");
	printf("将修改后的数据写入\n");
	while(p){
		fprintf(fp,"%40s %30s %30s %40s\n",p->name,p->singer,p->type,p->date);
		printf(">>>%-40s %-30s %-30s %-40s\n",p->name,p->singer,p->type,p->date);
		p = p->next;
 	}
	while(head){
		pt = head;
		head = head->next;
		free(pt);
	}//清理存储到链表中的数据
	fclose(fp);
	line;
}

struct song* read(void){
	FILE *fp;
	struct song *p1,*p2,*head_f;
	fp = fopen(song_info,"r");
	if(feof(fp)) {
		printf("数据为空\n");
		return  NULL;
	}
	p1 = (struct song *)malloc(sizeof(struct song));
	fscanf(fp,"%40s%30s%30s%40s\n",p1->name,p1->singer,p1->type,p1->date);
	//printf("%-40s %-30s %-30s %-10s\n",p1->name,p1->singer,p1->type,p1->date);//测试
	head_f = p1;
	while(!feof(fp)){
		p2 = p1;
		p1 = (struct song *)malloc(sizeof(struct song));
		p2->next = p1;
		fscanf(fp,"%40s%30s%30s%40s\n",p1->name,p1->singer,p1->type,p1->date);
		//printf("%-40s %-30s %-30s %-10s\n",p1->name,p1->singer,p1->type,p1->date);//测试
	}
	p1->next = NULL;
	fclose(fp);
	return head_f;
}

void print_file(void){
	line;
	FILE *fp;
	int count = 0;
	fp = fopen(song_info,"r");
	printf("%-40s %-30s %-30s %-40s\n",_song,_singer,_company,_date);
	while(1){
	fscanf(fp,"%40s %30s %30s %40s",sg.name,sg.singer,sg.type,sg.date);
	count++;
	if(feof(fp)) break;
	printf("%-40s %-30s %-30s %-40s\n\n",sg.name,sg.singer,sg.type,sg.date);
	}
	fclose(fp);
	line;
	printf("总共存储%d首歌曲的信息。",count);
}

void change_file(void){
	line;
	char s[30],ch;
	struct song *head = read();
	struct song *pf;
	print(head);
	printf("请输入要修改的歌曲名(#结束修改)\n>>");
	scanf("%s",s);
	while(s[0]!='#'){
		pf = head;
		while(pf){
			if(strcmp(s,pf->name)==0) break;
			pf = pf->next;
		}
		if(pf!=NULL){
			printf("%s->",pf->name);
			scanf("%s",pf->name);
			printf("%s->",pf->singer);
			scanf("%s",pf->singer);
			printf("%s->",pf->type);
			scanf("%s",pf->type);
			printf("%s->",pf->date);
			scanf("%s",pf->date);
			printf("- - - - - - - - -修改数据成功- - - - - - - - -\n");
		}
			else printf("文件中存储的歌曲信息中无\"%s\"此歌曲的信息!\n",s);
		printf("请输入要修改的歌曲名(#结束修改)\n>>");
		scanf("%s",s);
	}
	line;
	while(getchar()!='\n')
		continue;
	printf("如果您修改或删除了从文件中读取的数据，请注意记得保存它!(Y/N)\n>>");
	scanf("%c",&ch);
	if(ch=='Y') save_f(head);
		else {
			if(ch=='N') printf("您没有进行文件数据的修改!\n");
				else printf("默认未将文件数据进行更新\n");
			while(head){
				pf = head;
				head = head->next;
				free(pf);
			}
		}
}

void dele_file(void){
	line;
	struct song *head = read();
	struct song *pre,*head_t,*pf;
	char s[30],ch;
 	head_t = createhead();
 	head_t->next = head;
 	print(head_t);
	printf("请输入要删除的歌曲名(#结束删除)\n>>");
	scanf("%s",s);
	while(s[0]!='#')//可以多次删除结点
	{
		pre = head_t;
		pf = head;
		while(pf){
			if(strcmp(s,pf->name)==0) break;
			pf = pf->next;
			pre = pre->next;
		}
		if(pf!=NULL){
			pre->next = pf->next;
			free(pf);
			printf("- - - - - - - - -删除成功- - - - - - - - -\n");
		}
			else printf("文件存储的歌曲信息中无\"%s\"此歌曲!\n",s);
		printf("请输入要删除的歌曲名(#结束删除)\n>>");
		scanf("%s",s);
	}
	line;
	while(getchar()!='\n')
		continue;
	printf("如果您修改或删除了从文件中读取的数据，请注意记得保存它!(Y/N)\n>>");
	scanf("%c",&ch);
	if(ch=='Y') save_f(head);
		else {
			if(ch=='N') printf("您没有进行文件数据的修改!\n");
				else printf("默认未将文件数据进行更新\n");
				while(head){
					pf = head;
					head = head->next;
					free(pf);
				}
		}
}

void search_file(void){
	printf("\n如果您输入的搜索内容在歌曲名称或者歌手名称中出现了，则会打印出该歌曲信息。\n");
	line;
	FILE *fp = fopen(song_info,"r");
	char s[30];
	int i,j,k,flag;
	bool result;
	printf("请输入要查询到歌曲(#结束查询)\n>>>");
	scanf("%s",s);
	printf("%-40s %-30s %-30s %-40s\n\n",_song,_singer,_company,_date);
	while(s[0]!='#'){
		result = 0;
  		while(1){
			fscanf(fp,"%40s %30s %30s %40s",sg.name,sg.singer,sg.type,sg.date);
			if(feof(fp)) break;
			flag = 0;
			for(i = 0;i < strlen(sg.name);i++){
				k = i;
				j = 0;
				while(j < strlen(s)){
					if(sg.name[k++] == s[j++]);
						else break;
				}
				if(j==strlen(s)){
					printf("%-40s %-30s %-30s %-40s\n\n",sg.name,sg.singer,sg.type,sg.date);
					flag = 1;
					result = 1;
					break;
				}
			}//s字符串与歌曲名称中的某段匹配
			if(flag==0){
				for(i = 0;i < strlen(sg.singer);i++){
					k = i;
					j = 0;
					while(j < strlen(s)){
						if(sg.singer[k++] == s[j++]);
							else break;
					}
					if(j==strlen(s)){
						printf("%-40s %-30s %-30s %-40s\n\n",sg.name,sg.singer,sg.type,sg.date);
						result = 1;
						break;
					}
				}
			}//s字符串与歌手的字符串中的某段匹配
		}
		if(result==0)printf("- - - - - - - - - - - - - - 文件中存储的歌曲信息中无\"%s\"此歌曲! - - - - - - - - - - - - - - -\n",s);
		rewind(fp);
		printf("请输入要查询到歌曲(#结束查询)\n>>>");
		scanf("%s",s);
	}
	line;
	fclose(fp);
}

void sort_f(void){
	struct song *pf;
	pf = read();
	if(pf==NULL) {
		printf("文件为空\n");
		return;
	}
	line;
	int num = 0,i,j,k,option;
	struct song *head_f = pf;
	while(pf){
		pf = pf->next;
		num++;
	}
	pf = head_f;
	struct song *pt[num],*t = NULL;//定义指针数组指向链表各个结点，排序指针
	for(i = 0;i<num;i++){
		pt[i] = pf;
		pf = pf->next;
	}
	while(getchar()!='\n')
		continue;
	printf("如果您希望按A-z排序：>>1\n");
	printf("如果您希望按z-A排序：>>0\n>>");
	scanf("%d",&option);
	if(option==0){
		for(i = 0;i<num-1;i++){
			k = i;
			for(j = i+1;j<num;j++)
				if(strcmp(pt[k]->name,pt[j]->name)>0) k = j;
			if(k!=i){
				t = pt[i];
				pt[i] = pt[k];
				pt[k] = t;
			}
		}
		printf("%-40s %-30s %-30s %-40s\n",_song,_singer,_company,_date);
		for(i = 0;i<num;i++)
		printf("%-40s %-30s %-30s %-40s\n\n",pt[i]->name,pt[i]->singer,pt[i]->type,pt[i]->date);
	}
	else{
		 for(i = 0;i<num-1;i++){
			k = i;
			for(j = i+1;j<num;j++)
				if(strcmp(pt[k]->name,pt[j]->name)<0) k = j;
			if(k!=i){
				t = pt[i];
				pt[i] = pt[k];
				pt[k] = t;
			}
		}
		printf("%-40s %-30s %-30s %-40s\n",_song,_singer,_company,_date);
		for(i = 0;i<num;i++)
		printf("%-40s %-30s %-30s %-40s\n\n",pt[i]->name,pt[i]->singer,pt[i]->type,pt[i]->date);
	}
	line;
}





void help(void){
	line;
	system("color 02");
	char ch,option;
	while(getchar()!='\n')
		continue;
	printf("是否需要查看该系统的源文件？(Y/N)\n");
	printf("如果未输入Y则默认不查看。\n>>");
	scanf("%c",&option);
	FILE *fp,*f;
	if(option=='Y'){
		line;
		f = fopen(orgin_c,"r");
  	    ch = fgetc(f);
		while(!feof(f))
		{
			putchar(ch);
			ch = fgetc(f);
		}
		fclose(f);
	}
	fp = fopen(help_file,"r");
	printf("\n");
	line;
	printf("帮助信息：\n\n");
	ch = fgetc(fp);
	while(!feof(fp))
	{
		putchar(ch);
		ch = fgetc(fp);
	}
	fclose(fp);
}

void scheme(void){
	char font,bg;
	printf("\n请选择主题配置(配置第一个颜色为背景色，第二个颜色为字体色)\n");
    printf("注意：如果输入多个数字或字母只会读取第一个，如果未选择以下配置则默认为<淡蓝/亮黄>;\n");
    printf("如果输入的错误数字或字母被读取则配置会修改为默认配置;\n\n");
    printf("   字体或背景颜色属性由数字或字母指定:\n");
	printf("    配置      背景          字体\n");
	printf("    白/蓝      7             1\n");
	printf("    白/灰      7             8\n");
	printf("    白/黑      f             0\n");
	printf("    白/绿      f             2\n");
	printf("    白/蓝绿    f             b\n");
	printf("    白/红      f             c\n");
	printf("    灰/亮蓝    8             b\n");
	printf("    灰/黄      8             6\n");
	printf("    灰/白      8             7\n");
	printf("    蓝绿/红    b             c\n");
	printf("    蓝绿/黑    b             0\n");
	printf("    黑/蓝      0             1\n");
	printf("    黑/浅绿    0             3\n");
	printf("    黑/亮绿    0             a\n");
	printf("    黑/亮蓝    0             b\n");
	printf("    黑/淡红    0             c\n");
	printf("    黑/亮黄    0             e\n");
	printf("    黑/白      0             f\n\n");
	printf("\t推荐主题：\n");
	printf("\t>>>经典系列:f0/0f\n\n");
	printf("\t>>>少女系列：0b/0c/0e\n\n");
	printf("\t>>>少年系列：8b/03/0a\n\n");
	printf("只要提示下输入相应的数字即可完成主题设置。\n");
	while(getchar()!='\n');
	printf("请输入您希望设置的背景颜色:\n>>");
	scanf("%c",&font);
	while(getchar()!='\n');
	printf("请输入您希望设置的字体颜色:\n>>");
	scanf("%c",&bg);
	if(font=='7' && bg=='1') system("color 71");
	else if(font=='7' && bg=='8') system("color 78");
	else if(font=='f' && bg=='0') system("color f0");
	else if(font=='f' && bg=='2') system("color f2");
	else if(font=='f' && bg=='b') system("color fb");
	else if(font=='f' && bg=='c') system("color fc");
	else if(font=='8' && bg=='b') system("color 8b");
	else if(font=='8' && bg=='6') system("color 86");
	else if(font=='8' && bg=='7') system("color 87");
	else if(font=='b' && bg=='0') system("color b0");
	else if(font=='b' && bg=='c') system("color bC");
	else if(font=='0' && bg=='1') system("color 01");
	else if(font=='0' && bg=='3') system("color 03");
	else if(font=='0' && bg=='a') system("color 0a");
	else if(font=='0' && bg=='b') system("color 0b");
	else if(font=='0' && bg=='c') system("color 0c");
	else if(font=='0' && bg=='e') system("color 0e");
	else if(font=='0' && bg=='f') system("color 0f");
	else system("color 3e");
	printf("- - - - - - - - - -设置成功！- - - - - - - - - -\n");
}

void backup_f()
{
	FILE *fp,*f;
	char ch;
	if( (fp = fopen(song_info,"r"))==NULL ) {
		printf("D:\\data\\song_info.txt为空\n");
		return;
	}
	f = fopen(backup,"a");
	printf("写入>>>\n");
	while(!feof(fp)){
		ch = getc(fp);
		printf("%c",ch);
		fprintf(f,"%c",ch);
	}
	fprintf(f,"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"
	" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -%d\n",time(NULL));
	printf("备份\"D:\\data\\song_info.txt\" -> \"D:\\data\\歌曲信息管理系统\\song_backup.txt\"成功!\n");
	fclose(fp);
	fclose(f);
}

int main()
{
	system("mode con cols=200 lines=1000");
	//启动提示
	printf("\n\n\n\n\n\n\n");
	printf("    ________________________________________________\n");
	printf("    |>>>>>>>>>>>>>> 歌曲信息管理系统 <<<<<<<<<<<<<<|\n");
	printf("    |                                              |\n");
	printf("    |                                              |\n");
 	printf("    |                                              |\n");
	printf("    |                                              |\n");
	printf("    |            欢迎您使用歌曲管理系统！          |\n");
	printf("    |                作者：劣等生                  |\n");
   	printf("    |                                              |\n");
	printf("    |                                              |\n");
	printf("    |                                              |\n");
	printf("    |______________________________________________|\n");
	printf("                        >>start");
	system("pause>nul");
	system("cls");
	struct song *head = NULL;
	char option[3],ch;
	int i;
	menu();
	scanf("%s",option);
	while(1){
		if(strcmp(option,order[0])==0) break;
		else if(strcmp(option,order[1])==0){
			head = input();
		}
		else if(strcmp(option,order[2])==0){
			print(head);
		}
		else if(strcmp(option,order[3])==0){
			change(head);
		}
		else if(strcmp(option,order[4])==0){
			dele(head);
		}
		else if(strcmp(option,order[5])==0){
			search(head);
		}
		else if(strcmp(option,order[6])==0){
			save(head);
			head = NULL;
		}
		else if(strcmp(option,order[7])==0){
			print_file();
		}
		else if(strcmp(option,order[8])==0){
			change_file();//修改从文件读取到链表副本中的数据
		}
		else if(strcmp(option,order[9])==0){
			dele_file();//删除从文件读取到链表副本中的一些数据
		}
		else if(strcmp(option,order[10])==0){
   			search_file();
		}
		else if(strcmp(option,order[11])==0){
			sort_f();
		}
		else if(strcmp(option,order[12])==0){
			backup_f();
		}
		else if(strcmp(option,order[13])==0){
			help();
			system("pause>nul");
			system("color 07");
		}
		else if(strcmp(option,order[14])==0){
			scheme();
		}
		else {
			while(getchar()!='\n')
				continue;
		}
		system("pause>nul");
		system("cls");
		menu();
		scanf("%s",option);
	}
	return 0;
}
