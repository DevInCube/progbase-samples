#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct {
	char name[100];
	char faculty[100];
} Group;

typedef struct {
	char  	name[100];
	char  	surname[100];
	int 	year;
	float	score; 
	Group group;
} Student;

int readXml(void);
bool readAllText(const char * filename, char * text, int maxSize);
char * writeStudentToXmlString(Student * st, char * buffer);
int readXmlToStudents(const char * xmlStr, Student students[], int maxSize);

int main(void) {
	Student student = {
		.name = "Taras",
		.surname = "Kartoplia",
		.year = 1990,
		.score = 4.9,
		.group = {
			.name = "KP-51",
			.faculty = "PBF",
		}
	};
	char buffer[10000];
	printf("Student in XML:\n%s\n\n", writeStudentToXmlString(&student, buffer));
	free(memset(malloc(10000), 0, 10000));
	if (readAllText("students.xml", buffer, 10000)) {
		Student students[10];
		int stCount = readXmlToStudents(buffer, students, 10);
		for (int i = 0; i < stCount; i++) {
			printf("Student[%i]:\n%s %s %i %f\n", 
				i,
				students[i].name,
				students[i].surname,
				students[i].year,
				students[i].score);
		}
	}

	puts("");
	xmlCleanupParser();
	xmlMemoryDump();
	return 0;
}

char * writeStudentToXmlString(Student * st, char * buffer) {
	
	xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * studentNode = NULL;
	xmlNode * groupNode = NULL;
	char strBuf[100];
	
	doc = xmlNewDoc(BAD_CAST "1.0");

	// create xml tree

	// create one root element
	rootNode = xmlNewNode(NULL, BAD_CAST "students");
	xmlDocSetRootElement(doc, rootNode);
	
	// student child
	studentNode = xmlNewChild(rootNode, NULL, BAD_CAST "student", NULL);
	xmlNewChild(studentNode, NULL, BAD_CAST "name", BAD_CAST st->name);
	xmlNewChild(studentNode, NULL, BAD_CAST "surname", BAD_CAST st->surname);
	sprintf(strBuf, "%i", st->year);  // copy number to string
	xmlNewChild(studentNode, NULL, BAD_CAST "year", BAD_CAST strBuf);
	sprintf(strBuf, "%f", st->score);  // copy number to string
	xmlNewChild(studentNode, NULL, BAD_CAST "score", BAD_CAST strBuf);
	// create group element as student child
	groupNode = xmlNewChild(studentNode, NULL, BAD_CAST "group", NULL);
	xmlNewProp(groupNode, BAD_CAST "name", BAD_CAST st->group.name);
	xmlNewChild(groupNode, NULL, BAD_CAST "faculty", BAD_CAST st->group.faculty);
	
	// copy xml contents to char buffer
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	strcpy(buffer, (char *)bufferPtr->content);
	xmlBufferFree(bufferPtr);
	
    xmlFreeDoc(doc);
	return buffer;
}

int readXmlToStudents(const char * xmlStr, Student students[], int maxSize) {
	int count = 0;
	xmlDoc * xDoc = xmlReadMemory(xmlStr, strlen(xmlStr), NULL, NULL, 0);
    if (NULL == xDoc) {
        printf("Error parsing xml");
        return 0;
    }
    xmlNode * xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ; xCur = xCur->next) {
        if (XML_ELEMENT_NODE == xCur->type) {
            for (xmlNode * xJ = xCur->children; NULL != xJ ; xJ = xJ->next) {
                if (XML_ELEMENT_NODE == xJ->type) {
					char * content = (char *)xmlNodeGetContent(xJ);
					if (xmlStrcmp(xJ->name, BAD_CAST "group") == 0) {
                        xmlNode * xGroup = xJ;
						char * name = (char *)xmlGetProp(xGroup, BAD_CAST "name");
						strcpy(students[count].group.name, name);
						strcpy(students[count].group.faculty, content);
						xmlFree(name);
                    } else if (xmlStrcmp(xJ->name, BAD_CAST "name") == 0) {
						strcpy(students[count].name, (char *) content);
					} else if (xmlStrcmp(xJ->name, BAD_CAST "surname") == 0) {
						strcpy(students[count].surname, (char *) content);
					}
					// @todo
					students[count].score = 4.5;
					students[count].year = 1990;
					xmlFree(content);
                }
            }
			count += 1;
        }
    }
	xmlFreeDoc(xDoc);
	return count;
}

int readXml(void) {
	const char * inFile = "students.xml";
    char text[1000] = "";
	if (!readAllText(inFile, text, 1000)) {
		printf("Error reading %s\n", inFile);
		return 1;
	}

    xmlDoc * xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if (NULL == xDoc) {
        printf("Error parsing xml");
        return 1;
    }
    xmlNode * xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ; xCur = xCur->next) {
        if (XML_ELEMENT_NODE == xCur->type) {
            printf("Tag name <%s>\n", xCur->name);

            for (xmlNode * xJ = xCur->children; NULL != xJ ; xJ = xJ->next) {
                if (XML_ELEMENT_NODE == xJ->type) {
					if (xmlStrcmp(xJ->name, BAD_CAST "group") == 0) {
                        xmlNode * xGroup = xJ;
                        xmlNode * xFac = xGroup->children->next;
						char * name = (char *)xmlGetProp(xGroup, BAD_CAST "name");
						char * fac = (char *)xmlNodeGetContent(xFac);
                        printf("\t%10s: %s (%s)\n", "group", name, fac);
						xmlFree(name);
						xmlFree(fac);
                        continue;
                    }
					char * content = (char *)xmlNodeGetContent(xJ);
                    printf("\t%10s: %s\n", xJ->name, content);
					xmlFree(content);
                }
            }
        }
    }
	xmlFreeDoc(xDoc);
    return 0;
}

bool readAllText(const char * filename, char * text, int maxSize) {
	char line[100];
    memset(text, 0, maxSize);
    FILE * fr = fopen(filename, "r");
	if (fr == NULL) return false;
    while(fgets(line, 100, fr)) {
        strcat(text, line);
    }
	fclose(fr);
	return true;
}
