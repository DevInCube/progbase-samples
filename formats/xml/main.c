#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct {
	char * name;
	char * faculty;
} Group;

typedef struct {
	char * 	name;
	char * 	surname;
	int 	year;
	float	score; 
	Group group;
} Student;

int writeXml(void);
int readXml(void);

int main() {
	readXml();
	puts("");
	writeXml();
	return 0;
}

int writeXml(void) {
	Student st = {
		.name = "Taras",
		.surname = "Kartoplia",
		.year = 1990,
		.score = 4.9,
		.group = {
			.name = "KP-51",
			.faculty = "PBF",
		}
	};

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
	xmlNewChild(studentNode, NULL, BAD_CAST "name", BAD_CAST st.name);
	xmlNewChild(studentNode, NULL, BAD_CAST "surname", BAD_CAST st.surname);
	sprintf(strBuf, "%i", st.year);  // copy number to string
	xmlNewChild(studentNode, NULL, BAD_CAST "year", BAD_CAST strBuf);
	sprintf(strBuf, "%f", st.score);  // copy number to string
	xmlNewChild(studentNode, NULL, BAD_CAST "score", BAD_CAST strBuf);
	// create group element as student child
	groupNode = xmlNewChild(studentNode, NULL, BAD_CAST "group", NULL);
	xmlNewProp(groupNode, BAD_CAST "name", BAD_CAST st.group.name);
	xmlNewChild(groupNode, NULL, BAD_CAST "faculty", BAD_CAST st.group.faculty);
	
	// copy xml contents to char buffer
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	printf("%s", (const char *)bufferPtr->content);
	xmlBufferFree(bufferPtr);
	
    xmlFreeDoc(doc);
}

void readAllText(const char * filename, char * text) {
	char line[100];
    
    FILE * fr = fopen(filename, "r");
    while(fgets(line, 100, fr)) {
        strcat(text, line);
    }
	fclose(fr);
}


int readXmlToStudents(const char * xmlStr, Student students[], int maxSize) {
	int count = 0;
	xmlDoc * xDoc = xmlReadMemory(xmlStr, strlen(xmlStr), NULL, NULL, 0);
    if (NULL == xDoc) {
        printf("Error parsing xml");
        return 1;
    }
    xmlNode * xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ; xCur = xCur->next) {
        if (XML_ELEMENT_NODE == xCur->type) {
            for (xmlNode * xJ = xCur->children; NULL != xJ ; xJ = xJ->next) {
                if (XML_ELEMENT_NODE == xJ->type) {
					char * content = (char *)xmlNodeGetContent(xJ);
					if (xmlStrcmp(xJ->name, BAD_CAST "group") == 0) {
                        xmlNode * xGroup = xJ;
                        xmlNode * xFac = xGroup->children->next;
						char * name = (char *)xmlGetProp(xGroup, BAD_CAST "name");
						students[count].group = (Group) {
							.name = name,
							.faculty = content
						};
						xmlFree(name);
                    } else if (xmlStrcmp(xJ->name, BAD_CAST "name") == 0) {
						strcpy(students[count].name, (char *) content);
					} else if (xmlStrcmp(xJ->name, BAD_CAST "surname") == 0) {
						strcpy(students[count].surname, (char *) content);
					}
					// @todo
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
    char text[1000] = "";
	readAllText("students.xml", text);

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