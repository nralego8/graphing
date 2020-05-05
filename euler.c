#include <stdio.h>
#include <string.h>

#define MAX_SIZE 15000
#define BUFFER_SIZE 100

double h; // step size for Euler approximation

double t_first;
double t_max; // max t value, one we want to find
double t = 1; // initial t value
double y = 0; // initial y value

double f(double t, double y) {
	// return the result of our function
	return (3*t*t/(3*y*y-4));
}

// generates euler.html
void make_html(char *equation) {
	FILE *fp = fopen("euler.html", "w");
	fprintf(fp, "<title>Euler Grapher by Nolan</title>\n");
	fprintf(fp, "<script src=\"https://www.desmos.com/api/v1.5/calculator.js?apiKey=dcb31709b452b1cf9dc26972add0fda6\"></script>\n");
	fprintf(fp, "<body><div id=\"calculator\" style=\"position: absolute; top: 0; left: 0; width: 100%%; height: 100%%;\"></div></body>\n");
	fprintf(fp, "<script>\n\tvar elt = document.getElementById('calculator');\n");
  	fprintf(fp, "\tvar calculator = Desmos.GraphingCalculator(elt);\n");
	fprintf(fp, "\tcalculator.updateSettings({invertedColors: 'true'});\n");
  	fprintf(fp, "\tcalculator.setExpression({ id: 'graph1', color: '#F54576', latex: 'f(x)=\\\\left\\\\{%s\\\\right\\\\}' });\n", equation);
	fprintf(fp, "\tcalculator.setExpression({ id: 'point1', latex: '(%0.2f,f(%0.2f))', showLabel: 'true'});\n", t_max, t_max);
	fprintf(fp, "\tcalculator.setExpression({ id: 'point2', latex: '(a,f(a))', showLabel: 'true'});\n");
	fprintf(fp, "\tcalculator.setExpression({ id: 'slider1', latex: 'a=%0.2f', sliderBounds: { min: %0.2f, max: %0.2f, step: %0.2f}});\n", t_first, t_first, t_max, h);
	fprintf(fp, "\n</script>\n");
}

int main()
{
	char equation[MAX_SIZE];
	char buffer[BUFFER_SIZE];
	
	printf("Enter t you want to find: ");
	scanf("%lf", &t_max);
	
	printf("Enter step size: ");
	scanf("%lf", &h);

	t_first = t;
	int accuracy = 6; // how many digits to use in desmos
	double t_before; // t of previous iteration
	double y_before; // y pf previous iteration	
	double result; // used to store result of f(t,y)
	
	int pieces = 0; // used to keep track of the pieces used 

	while(pieces < (t_max-t_first)/h) {
		result = f(t,y);
		t_before = t;
		y_before = y;
		y += result*h;
		t+=h;
		if(strlen(equation) >= (MAX_SIZE-BUFFER_SIZE)) { 
			printf("Not enough memory!\nDisplaying last value calculated:\n");
			break;
		}
		sprintf(buffer, "%0.2f\\\\le x \\\\le %0.2f:%0.*f+%0.*f(x-%0.2f),", t_before, t, accuracy, y_before, accuracy, result, t_before);
		strcat(equation, buffer);
		pieces++;
	}
	printf("t = %0.3f, y = %f\n", t, y);
	equation[strlen(equation)-1] = '\0'; // removes the last comma 
	make_html(equation);
	printf("Finalized piecewise function using %d pieces!\n", pieces);
	return 0;
}
