
#include "Functions.h"

const int size = 29;
using vector3d = std::vector<std::vector<std::vector<int>>>;


void Functions::read_kb(unsigned char key)
{


	switch (key) {

	
		
	case '\x1b':
		exit(1);
		break;
    case '+':
        zoom += 50;
        break;
    case '-':
        zoom -= 50;
        break;

    case 'q':
        anglex += 10;
        break;
    case 'e':
        anglex -= 10;
        break;
    case 'z':
        anglex -= 10;
        break;
    case 'x':
        angley -= 10;
        break;
    case 'c':
        anglez -= 10;
        break;


	}
	glutPostRedisplay();


}
void Functions::read_speckb(int k) {
    
}


    vector3d Functions::start() {
       
        vector3d mat(size, std::vector<std::vector<int>>(size, std::vector<int>(size, 0)));
       
            int countpr;
            
            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                    for (int k = 0; k < size; ++k)
                        mat[i][j][k] = 0;
            std::cout << "введите количество препядствий ";
            std::cin >> countpr;
            for (int i = 0; i < countpr; i++) {
                int x = 0, y = 0, z = 0;
                std::cin >> x;
                std::cin >> y;
                std::cin >> z;

                while (mat[x][y][z] == 1) {
                    std::cout << "эти координаты препядствия уже заняты, введите другие ";
                    std::cin >> x;
                    std::cin >> y;
                    std::cin >> z;
                }
                mat[x][y][z] = -2;

            }

            std::cout << "введите координаты начала  ";
            
            
                int x = 0, y = 0, z = 0;
                std::cin >> x;
                std::cin >> y;
                std::cin >> z;

                while (mat[x][y][z] == -2) {
                    std::cout << "эти координаты препядствия уже заняты, введите другие ";
                    std::cin >> x;
                    std::cin >> y;
                    std::cin >> z;
                }
                mat[x][y][z] = -1;

                std::cout << "введите координаты конца ";

                std::cin >> x;
                std::cin >> y;
                std::cin >> z;

                while (mat[x][y][z] == -1 or mat[x][y][z] == -2) {
                    std::cout << "эти координаты препядствия уже заняты, введите другие ";
                    std::cin >> x;
                    std::cin >> y;
                    std::cin >> z;
                }
                mat[x][y][z] = -3;




            out(mat);
            return mat;
            // Передача по ссылке копирования не вызывает
        }
    
    
  void Functions::out(const vector3d & mat)
        {
            for (int i = 0; i < mat.size(); ++i)
            {
                for (int j = 0; j < mat[i].size(); ++j)
                {
                    for (int k = 0; k < mat[i][j].size(); ++k)
                        std::cout << mat[i][j][k] << " ";
                    std::cout << std::endl;
                }
                std::cout << std::endl << std::endl << std::endl;
            }
        }

  void Functions::draw(const vector3d& mat, bool flagdraw) {
      float koef = 50 / size;
      glLoadIdentity();
      glTranslatef(0, 0, zoom);
      glRotatef(anglex, 1, 0, 0);
      glRotatef(angley, 0, 1, 0);
      glRotatef(anglez, 0, 0, 1);
      
       
      int i = -size / 2;
      int j = -size / 2;
      for (int k = -size / 2 ; k < size / 2 + 1; k ++) {
                  
          for ( i = -size / 2 ; i < size/2 + 1; i ++ ) {
              glBegin(GL_LINES);
               glVertex3f( i * koef, 1 * koef * size/2 , k * koef  );
               glVertex3f( i * koef, -1 * koef * size /2, k * koef );
               glEnd();
               for ( j = -size / 2; j < size / 2 + 1; j ++ ) {
                   glBegin(GL_LINES);
                   glVertex3f(1 * koef * size/2, j * koef, k * koef );
                   glVertex3f(-1 * koef * size /2, j * koef, k * koef );
                   glEnd();
               } 
          } 
      } 
      for (i = -size / 2; i <= size / 2; i ++) {
          for (j = -size / 2; j <= size / 2; j ++) {
              glBegin(GL_LINES);
              glVertex3f(i * koef , j * koef , -1 * koef * size / 2);
              glVertex3f(i * koef , j * koef , 1 * koef * size / 2);
              glEnd();
          } 
      } 
      

      for (int i = 0; i < mat.size(); ++i)
      {
          for (int j = 0; j < mat[i].size(); ++j)
          {
              for (int k = 0; k < mat[i][j].size(); ++k)
              {
                  if (mat[i][j][k] == -2 ) {
                      glBegin(GL_QUADS);
                      // Левая грань
                      glColor3f(0.0f, 1.0f, 0.0f);  
                      glVertex3f((i - size /2) * koef , (j - size / 2)* koef, (k - size / 2) * koef );
                      glVertex3f((i - size / 2) * koef  , ( j - size / 2 ) * koef, (k + 1 - size /2) * koef);
                      glVertex3f((i - size / 2 ) * koef , (j + 1 - size / 2) * koef , (k + 1 - size / 2) * koef);
                      glVertex3f((i - size / 2 ) * koef , (j + 1 - size / 2) * koef , (k - size / 2) * koef);

                      // Задняя грань
             
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2 ) * koef);

                      // Передняя грань
                      
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);

                      // Правая грань
                        
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);

                      // Верхняя грань
                      
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);

                      // Нижняя грань
                     
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glEnd();
                  } 

              } 
          }
          
      }
      
      for (int i = 0; i < mat.size(); ++i)
      {
          for (int j = 0; j < mat[i].size(); ++j)
          {
              for (int k = 0; k < mat[i][j].size(); ++k)
              {
                  if (mat[i][j][k] == -1) {
                      glBegin(GL_QUADS);
                      // Левая грань
                      glColor3f(1.0f, 0.0f, 0.0f);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k + 1 - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j + 1 - size / 2) * koef, (k + 1 - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j + 1 - size / 2) * koef, (k - size / 2) * koef);

                      // Задняя грань
                 
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);

                      // Передняя грань
                     
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);

                      // Правая грань
                     
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);

                      // Верхняя грань
                     
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);

                      // Нижняя грань
                     
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glEnd();
                  }

              }
          }

      }

      for (int i = 0; i < mat.size(); ++i)
      {
          for (int j = 0; j < mat[i].size(); ++j)
          {
              for (int k = 0; k < mat[i][j].size(); ++k)
              {
                  if (mat[i][j][k] == -3) {
                      glBegin(GL_QUADS);
                      // Левая грань
                      glColor3f(0.0f, 0.0f, 1.0f);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k + 1 - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j + 1 - size / 2) * koef, (k + 1 - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j + 1 - size / 2) * koef, (k - size / 2) * koef);

                      // Задняя грань
                      
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);

                      // Передняя грань
                    
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);

                      // Правая грань
                   
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);

                      // Верхняя грань
                     
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);

                      // Нижняя грань
                     
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glEnd();
                  }

              }
          }

      }
         
      if (flagdraw ) 
      for (int i = 0; i < mat.size(); ++i)
      {
          for (int j = 0; j < mat[i].size(); ++j)
          {
              for (int k = 0; k < mat[i][j].size(); ++k)
              {
                  if (mat[i][j][k] > 0) {
                      glBegin(GL_QUADS);
                      // Левая грань
                      glColor3f(1.0f, 1.0f, 1.0f);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k + 1 - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j + 1 - size / 2) * koef, (k + 1 - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j + 1 - size / 2) * koef, (k - size / 2) * koef);

                      // Задняя грань

                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);

                      // Передняя грань

                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);

                      // Правая грань

                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);

                      // Верхняя грань

                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2 + 1) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);

                      // Нижняя грань

                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glVertex3f((i - size / 2) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2 + 1) * koef);
                      glVertex3f((i - size / 2 + 1) * koef, (j - size / 2) * koef, (k - size / 2) * koef);
                      glEnd();
                  }

              }
          }

      }

      
     
  }



  void Functions :: Axis() {
      
          glLoadIdentity();
          glTranslatef(-0.7, -0.6, - 2); // меняем центр
          float k = 10;
          glRotatef(anglex, 1, 0, 0);
          glRotatef(angley, 0, 1, 0);
          glRotatef(anglez, 0, 0, 1);


          glBegin(GL_LINES);
          glLineWidth(5);
          //x
          glColor3f(1, 0, 0);
          glVertex3f(0, 0, 0);
          glVertex3f(0.01 * k, 0, 0);
          //y
          glColor3f(0, 0, 1);
          glVertex3f(0, 0, 0);
          glVertex3f(0, 0.01 * k, 0);
          //z
          glColor3f(0, 1, 0);
          glVertex3f(0, 0, 0);
          glVertex3f(0, 0, 0.01 * k);
          glEnd();
      

  }

  enum cell {
      block = -2,
      begin = -1,
      final = -3,
      empty = 0
  };

  vector3d Functions::wave(const vector3d& mat) {
      vector3d trail(size, std::vector<std::vector<int>>(size, std::vector<int>(size, 0)));
     
      for (int i = 0; i < size; ++i)
          for (int j = 0; j < size; ++j)
              for (int k = 0; k < size; ++k)
                  trail[i][j][k] = mat[i][j][k];

      int x_a, y_a, z_a;
      for (int i = 0; i < mat.size(); ++i)
      {
          for (int j = 0; j < mat[i].size(); ++j)
          {
              for (int k = 0; k < mat[i][j].size(); k++) {
                  if (mat[i][j][k] == begin) {
                      x_a = i; y_a = j; z_a = k;
                  }

              }
          }
      }


      int wave = 1;
      if (x_a - 1 > 0)
      {
          if (trail[x_a - 1][y_a][z_a] == empty) {
              trail[x_a - 1][y_a][z_a] = wave;
          }
      }
      if (x_a + 1 < size)
      {
          if (trail[x_a + 1][y_a][z_a] == empty) {
              trail[x_a + 1][y_a][z_a] = wave;
          }
      }
      if (y_a - 1 > 0)
      {
          if (trail[x_a][y_a - 1][z_a] == 0) {
              trail[x_a][y_a - 1][z_a] = wave;
          }
      }
      if (y_a + 1 < size)
      {
          if (trail[x_a][y_a + 1][z_a] == empty) {
              trail[x_a][y_a + 1][z_a] = wave;
          }
      }
      if (z_a - 1 > 0)
      {
          if (trail[x_a][y_a][z_a - 1] == empty) {
              trail[x_a][y_a][z_a - 1] = wave;
          }
      }
      if (z_a + 1 < size)
      {
          if (trail[x_a][y_a][z_a + 1] == empty) {
              trail[x_a][y_a][z_a + 1] = wave;
          }
      }

      
      bool flag = true;
      bool flagfin = true;
      while (flag) {
          flag = false;
          wave += 1;
          for (int i = 0; i < mat.size(); ++i)
          {
              for (int j = 0; j < mat[i].size(); ++j)
              {
                  for (int k = 0; k < mat[i][j].size(); k++) {
  
                      if (trail[i][j][k] == wave-1)
                      {
                          if (i - 1 > 0)
                          {
                              if (trail[i - 1][j][k] == final) {
                                  flagfin = false;
                                  break;
                              } 
                              if ((trail[i - 1][j][k] != block || trail[i - 1][j][k] != begin || trail[i - 1][j][k] != final) && (trail[i - 1][j][k] == empty))
                              {
                                  trail[i - 1][j][k] = wave;
                                  flag = true;
                              }

                          }
                          if (i + 1 < mat.size())
                          {
                              if (trail[i + 1][j][k] == final) {
                                  flagfin = false;
                                  break;
                              }
                              if ((trail[i + 1][j][k] != block || trail[i + 1][j][k] != begin || trail[i + 1][j][k] != final) && (trail[i + 1][j][k] == empty))
                              {
                                  trail[i + 1][j][k] = wave;
                                  flag = true;
                              }
                          }
                          if (j - 1 > 0)
                          {
                              if (trail[i][j - 1][k] == final) {
                                  flagfin = false;
                                  break;
                              }
                              if ((trail[i][j - 1][k] != block || trail[i][j - 1][k] != begin || trail[i][j - 1][k] != final) && (trail[i][j - 1][k] == empty))
                              {
                                  trail[i][j - 1][k] = wave;
                                  flag = true;
                              }
                          }
                          if (j + 1 < mat[i].size())
                          {
                              if (trail[i][j + 1][k] == final) {
                                  flagfin = false;
                                  break;
                              }
                              if ((trail[i][j + 1][k] != block || trail[i][j + 1][k] != begin || trail[i][j + 1][k] != final) && (trail[i][j + 1][k] == empty))
                              {
                                  trail[i][j + 1][k] = wave;
                                  flag = true;
                              }
                          }
                          if (k - 1 > 0)
                          {
                              if (trail[i][j][k - 1] == final) {
                                  flagfin = false;
                                  break;
                              }
                              if ((trail[i][j][k - 1] != block || trail[i][j][k - 1] != begin || trail[i][j][k - 1] != final) && (trail[i][j][k - 1] == empty))
                              {
                                  trail[i][j][k - 1] = wave;
                                  flag = true;
                              }
                          }
                          if (k + 1 < mat[i][j].size())
                          {
                              if (trail[i][j][k + 1] == final) {
                                  flagfin = false;
                                  break;
                              }
                              if ((trail[i][j][k + 1] != block || trail[i][j][k + 1] != begin || trail[i][j][k + 1] != final) && (trail[i][j][k + 1] == empty))
                              {
                                  trail[i][j][k + 1] = wave;
                                  flag = true;
                              }
                          }
                          if (flagfin == false) {
                              flag = false;
                          } 




                      }
                  }
              }

          }
          
      }
      
     
      return  trail;
  } 


  int Functions :: mintrail(const vector3d& trail) {
      int mascorner[6] = { 0 };
      for (int i = 0; i < trail.size(); ++i)
      {
          for (int j = 0; j < trail[i].size(); ++j)
          {
              for (int k = 0; k < trail[i][j].size(); k++) {
                  if (trail[i][j][k] == -3) {
                      if (i - 1 > 0)
                          mascorner[0] = trail[i - 1][j][k];
                      if (i + 1 < size)
                          mascorner[1] = trail[i + 1][j][k];
                      if (j - 1 > 0)
                          mascorner[2] = trail[i][j - 1][k];
                      if (j + 1 < size)
                          mascorner[3] = trail[i][j + 1][k];
                      if (k - 1 > 0)
                          mascorner[4] = trail[i][j][k - 1];
                      if (k + 1 < size)
                          mascorner[5] = trail[i][j][k + 1];
                  }


              }
          }
      }
      int min = std::numeric_limits<int>::max();
      for (int i = 0; i < 6; i++) {
          if (min > mascorner[i] and mascorner[i] > 0) {
              min = mascorner[i];

          }
          std::cout << mascorner[i] << std::endl;
      }
      std::cout << "путь из точки А до точки Б = " << min << std::endl;
      return min;
  } 

  void Functions::reversetrail(const vector3d& mat, int min) {

      int x_b, y_b, z_b;
      for (int i = 0; i < mat.size(); ++i)
      {
          for (int j = 0; j < mat[i].size(); ++j)
          {
              for (int k = 0; k < mat[i][j].size(); k++) {
                  if (mat[i][j][k] == final) {
                      x_b = i; y_b = j; z_b = k;
                  }

              }
          }
      }
        std::vector <point> array;
        float koef = 50 / size;
        point a;
          a.x = x_b;
          a.y = y_b;
          a.z = z_b;
          array.push_back(a);

          int mascorner[6] = { 0 };
      bool flag = true;
      for (int wave = min; wave != 1; wave --) {
          if (a.x - 1 > -1) {
              if (mat[a.x - 1][a.y][a.z] == wave) {
                  a.x -= 1;
                  array.push_back(a);
                  continue;
              } 
          
          } 
          if (a.x + 1 <  size) {
              if (mat[a.x + 1][a.y][a.z] == wave) {
                  a.x += 1;
                  array.push_back(a);
                  continue;
              }

          }
          if (a.y - 1 > -1) {
              if (mat[a.x][a.y - 1][a.z] == wave) {
                  a.y -= 1;
                  array.push_back(a);
                  continue;
              }

          }
          if (a.y + 1 < size) {
              if (mat[a.x][a.y + 1][a.z] == wave) {
                  a.y += 1;
                  array.push_back(a);
                  continue;
              }

          }
          if (a.z - 1 > -1) {
              if (mat[a.x][a.y][a.z - 1] == wave) {
                  a.z -= 1;
                  array.push_back(a);
                  continue;
              }

          }
          if (a.z + 1  < size) {
              if (mat[a.x][a.y][a.z + 1] == wave) {
                  a.z += 1;
                  array.push_back(a);
                  continue;
              }

          }
          
      

      
      
      } 
      for (int i = 0; i < size; i ++) {
          for (int j = 0; j < size; j ++) {
              for (int k = 0; k < size; k ++ ) {
                  if (mat[i][j][k] == 1) {
                      a.x = i;
                      a.y = j; 
                      a.z = k;
                      goto stop1;
                  
                  } 
              
              } 
          
          } 
      
      } 
  stop1:
      
      array.push_back(a);
     

      
      
          for (int i = 1; i < array.size(); i ++ ) {
          
              glBegin(GL_QUADS);
              // Левая грань
              glColor3f(1.0f, 1.0f, 1.0f);
              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2) * koef);
              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2) * koef, (array[i].z + 1 - size / 2) * koef);
              glVertex3f((array[i].x - size / 2) * koef, (array[i].y + 1 - size / 2) * koef, (array[i].z + 1 - size / 2) * koef);
              glVertex3f((array[i].x - size / 2) * koef, (array[i].y + 1 - size / 2) * koef, (array[i].z - size / 2) * koef);

              // Задняя грань

              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2) * koef);
              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2) * koef);

              // Передняя грань

              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2) * koef);
              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2 + 1) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2 + 1) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2) * koef);

              // Правая грань

              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2 + 1) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2 + 1) * koef);

              // Верхняя грань

              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2 + 1) * koef);
              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2 + 1) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2 + 1) * koef, (array[i].z - size / 2 + 1) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2 + 1) * koef);

              // Нижняя грань

              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2) * koef);
              glVertex3f((array[i].x - size / 2) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2 + 1) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2 + 1) * koef);
              glVertex3f((array[i].x - size / 2 + 1) * koef, (array[i].y - size / 2) * koef, (array[i].z - size / 2) * koef);
              glEnd();
          }
          
          

                  
      } 
      
      /*
  pointn negtbors(const vector3d& mat, int x, int y, int z) {
      int mas[6] = { 0 };
      pointn a;
      if (x - 1 > 0) {
          a.xm = x - 1;
      }
      if (x + 1 < mat.size()) {
          a.xp = x + 1;
      }

      if (y - 1 > 0) {
           a.ym = y - 1;
      }

      if (y + 1 < mat.size()) {
          a.yp = y + 1;
      }
      if (z- 1 > 0) {
          a.zm = z - 1;
      }
      if (z + 1 < mat.size()) {
           a.zp = z + 1;

      }
  
      return a;
  };

  void Functions :: reversetrail1(const vector3d& mat) {
      int x_b, y_b, z_b;
      std::vector <point> array;
      bool flag = true;

      for (int i = 0; i < mat.size(); ++i)
          {
              for (int j = 0; j < mat[i].size(); ++j)
              {
                  for (int k = 0; k < mat[i][j].size(); k++) {
                      if (mat[i][j][k] == final) {
                          x_b = i; y_b = j; z_b = k;
                      }

                  }
              }
          }



      point a; 
      a.x = x_b;
      a.y = y_b;
      a.z = z_b;
      array.push_back(a);
      int mas[6] = {0};


      while(mat[a.x][a.y][a.z] != 1) {
       
         pointn n = negtbors(mat, a.x, a.y, a.z );
         mas[0] = n.xm;
         mas[1] = n.xp;
         mas[2] = n.ym;
         mas[3] = n.yp;
         mas[4] = n.zm;
         mas[5] = n.zp;

         int min = std::numeric_limits<int>::max();
         for (int i = 0; i < 6; i++) {
             if (min > mas[i] and mas[i] > 0) {
                 min = mas[i];

             }
             
         }

         for (int i = 0; i < 6; i ++) {
             if (min == mas[i]) {
             
                 if (i == 0) {
                     a.x = mas[0];
                 } 
                 if (i == 1) {
                     a.x = mas[1];
                 }
                 if (i == 2) {
                     a.y = mas[2];
                 }
                 if (i == 3) {
                     a.y = mas[3];
                 }
                 if (i == 4) {
                     a.z = mas[4];
                 }
                 if (i == 5) {
                     a.z = mas[5];
                 }


             } 
         
         } 
         array.push_back(a);
                 
                  



      } 


  }
 
 
  
  
  */