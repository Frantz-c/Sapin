#include <unistd.h> 

#define stdout 1

void echo(const char *str);
void cout(char c);
void Concat(char *s1, const char *s2);
int  length_of(const char *str);
int  Str_to_int(char *s);
void Draw_Fir(int n);
void Draw_FirBottom(int n, int fir_w);
void Set_FirData(int n, int *fir_w, int *p_bottom, int *p_head);


int main(int argc, char *argv[])
{
  int input = 0;
  char error_msg[180] = "\n\e[0;37mUsage :\n\n\e[1;37m";

  if (length_of(*argv) > 100) {
    echo("Nom de programme trop long");
    return -3;
  }

  Concat(error_msg, *argv);
  Concat(error_msg, " [int]\n\n\e[0;36m(int < 15 && > 0)\e[0m\n\n");


  if (argc != 2) {
    echo(error_msg);
    return -1;
  }

  if ((input = Str_to_int(argv[1])) < 1) return -2;
  Draw_Fir(input);

  return 0;
}

int Str_to_int(char *s)
{
  int n = 0;
  int len = length_of(s) - 1;
  int mul = 1;

  if (len > 2) { 
    echo("\e[1;31mNombre entré < à 0, > à 15 ou invalide\e[0m\n");
    return -1;
  }

  for (char *number = s + len; number >= s; mul *= 10, number--)
  {
    if (*number > '9' || *number < '0') {
      echo("\e[1;31mNombre entré invalide !\e[0m\n");
      return -2;
    }
    n += (*number - 48) * mul;
  }
  
  if (n == 0) {
    echo("\e[1;31mNombre entré < à 1\e[0m\n");
    return -3;
  }
  if (n > 15) {
    echo("\e[1;31mNombre entré > à 15\e[0m\n");
    return -4;
  }
  
  return n; 
}


void echo(const char *str)
{
  write(stdout, str, length_of(str));
}

void cout(char c)
{
  write(stdout, &c, 1);
}

void Concat(char *s1, const char *s2)
{
  int i;
  int s1l = length_of(s1);
  int s2l = length_of(s2);

  for (i = s1l; i < (s1l + s2l); i++)
  {
    s1[i] = *(s2++);
  }
}

int length_of(const char *str)
{
  int i;
  if (!str) return -1;
  for (i = 0; str[i] != 0; i++);
  return i;
}

/* Draw Fir Tree Functions ==================================================*/

void Draw_Fir(int n)
{
  int fir_w, p_bottom, offset, floor_offset, i, j, k, n_lines, line_w;

  Set_FirData(n, &fir_w, &p_bottom, &offset);
  echo("\e[0;32m");

  for (floor_offset = 0, line_w = 1, n_lines = 4, i = 0; i < n; i++)
  {
    line_w -= (floor_offset * 2);
    offset += floor_offset;
    for (j = 0; j < n_lines; j++)
    {
      for (k = 0; k < offset; k++) cout(' ');
      for (k = 0; k < line_w; k++) cout('*');
      cout('\n');
    
      if (j < n_lines - 1) {
        line_w += 2;
        offset--;
      }
    }

    n_lines++;
    if ( !(i % 2) ) floor_offset++;
  }
  
  echo("\e[0;33m");
  Draw_FirBottom(n, fir_w);

  echo("\e[0m\n");
}

void Draw_FirBottom(int n, int fir_w)
{
  int i, j;
  int offset = (fir_w - n) / 2;

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < offset; j++) cout(' ');
    for (j = 0; j < n; j++) cout('|');
    cout('\n');
  }
}

void Set_FirData(int n, int *fir_w, int *p_bottom, int *offset)
{
  int i, n_new_lines;
  *fir_w = 7;

  for (n_new_lines = 3, i = 1; i < n; i++)
  {
    *fir_w += n_new_lines * 2;
    if (i % 2) n_new_lines++;
  }

  *p_bottom = ((*fir_w) - n) / 2;
  *offset = (*fir_w) / 2;
}


