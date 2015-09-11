#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "cgic.h"

int cgiMain(int argc, char *argv[])
{
	MYSQL mysql;
	MYSQL_RES *res = NULL;
	MYSQL_ROW row;
	
	char 
	int ret;
	unsigned int i, count;
	char **name = NULL;
	char AreaName[20];
	char AreaLamp[20];
	char LampNum[10];
	
	//cgi 格式
	cgiHeaderContentType("text/html");
	//获取区域信息
	cgiFormString("AreaName",AreaName, 20);
	//获取路灯编号
	cgiFormString("LampNum", LampNum, 10);

	
	//查询街道区域
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, "localhost", "root", "pwd17951", "City", 0, NULL, 0))
	{
		ret = mysql_query(&mysql, "SELECT AreaLamp FROM cityarea WHERE AreaNameCN = '$AreaName' ");
		if(!ret)
		{
			fprintf(cgiOut, "<HTML><HEAD>/n");
			fprintf(cgiOut, "<TITLE>Query AreaName Error!</TITLE></HEAD>/n");
			fprintf(cgiOut, "<BODY><H1>Query AreaName Error!</H1></BODY>/n");
			fprintf(cgiOut, "</HTML>/n");
		}
		else
		{
			res = mysql_store_result(&mysql);
			if(res)
			{
				int i = 0;
				row = mysql_fetch_row(res);
				strcpy(AreaLamp, row[i]);
			}
			else
			{
				fprintf(cgiOut, "<HTML><HEAD>/n");
				fprintf(cgiOut, "<TITLE>No finding!</TITLE></HEAD>/n");
				fprintf(cgiOut, "<BODY><H1>Cannt find the AreaLamp!</H1></BODY>/n");
				fprintf(cgiOut, "</HTML>/n");
			}
		}
	}
	
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, "localhost", "root", "pwd17951", "City", 0 , NULL, 0))
	{
		ret = mysql_query(&mysql, "SELECT LightITS, CurrentITS FROM $AreaLamp WHERE LampNum = '$LampNum'");
		if(!ret)
		{
			fprintf(cgiOut, "<HTML><HEAD>/n");
			fprintf(cgiOut, "<TITLE>Query AreaLamp Error!</TITLE></HEAD>/n");
			fprintf(cgiOut, "<BODY><H1>Query AreaLamp Error!</H1></BODY>/n");
			fprintf(cgiOut, "</HTML>/n");
		}
		else
		{
			res = mysql_store_result(&mysql);
			if(res)
			{
				
				row = mysql_fetch_row(res);
				fprintf(cgiOut, "<HTML><HEAD>/n");
				fprintf(cgiOut, "<TITLE>Present Intensity!</TITLE></HEAD>/n");
				fprintf(cgiOut, "<BODY><H1>/n");
				int iCol = 0;
				while (iCol < res->field_count)
				{
					printf("%-10s ", res->fields[iCol].name);
					++iCol;
				}
				printf("\n");
				for(i = 0, i < res->field_count, i++)
					fprintf(cgiOut, "%d", row[0]);
				
				fprintf(cgiOut, "</H1></BODY>/n");
				fprintf(cgiOut, "</HTML>/n");
				
				mysql_free_result(res);
			}
		}
	}
	mysql_close(&mysql);
	free(&mysql);
	
}











