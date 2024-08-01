#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

GLdouble pos_carro = 0;
GLdouble rot_rodas = 0;
int cam_view = 0;

void render_floor() {
  glColor3f(0.5, 0.8, 0.5);
  glBegin(GL_LINES);
  for (GLfloat i = -100; i <= 100; i += 10) {
    glVertex3f(i, -5, 100);
    glVertex3f(i, -5, -100);
    glVertex3f(100, -5, i);
    glVertex3f(-100, -5, i);
  }
  glEnd();
}

// renderiza a cena
void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  render_floor();
  glPushMatrix();
  {
    glTranslatef(pos_carro, 0, 0); // translada o carro posição atual

    glPushMatrix(); // salva a matriz de transformação atual
    {
      glColor3f(1.0f, 0.0f, 0.0f); // cor do carro
      glScalef(40, 1, 20); // dimensões do carro
      glutSolidCube(1); // desenha o carro
    }
    glPopMatrix(); // restaura a matriz de transformação anterior

    glPushMatrix(); // Salva a matriz de transformação atual
    {
      glColor3f(0.25f, 0.25f, 0.25f); // cor da roda traseira esquerda
      glTranslatef(-20, 0, -10); // translada a roda traseira
      glutSolidTorus(1, 3, 15, 30); // desenha a roda traseira
    }
    glPopMatrix(); // restaura a matriz de transformação anterior

    glPushMatrix(); // salva a matriz de transformação atual
    {
      glColor3f(0.25f, 0.25f, 0.25f); // cor da roda traseira direita
      glTranslatef(-20, 0, 10); // translada a roda traseira direita
      glutSolidTorus(1, 3, 15, 30); // desenha a roda traseira direita
    }
    glPopMatrix(); // restaura a matriz de transformação anterior

    glPushMatrix(); // salva a matriz de transformação atual
    {
      glColor3f(0.25f, 0.25f, 0.25f); // cor da roda dianteira esquerda
      glTranslatef(20, 0, -10); // translada a roda dianteira esquerda
      glRotatef(rot_rodas, 0, 1, 0); // rotaciona a roda dianteira esquerda
      glutSolidTorus(1, 3, 15, 30); // desenha a roda dianteira esquerda
    }
    glPopMatrix(); // restaura a matriz de transformação anterior

    glPushMatrix(); // salva a matriz de transformação atual
    {
      glColor3f(0.25f, 0.25f, 0.25f); // cor da roda dianteira direita
      glTranslatef(20, 0, 10); // translada a roda dianteira direita
      glRotatef(rot_rodas, 0, 1, 0); // rotaciona a roda dianteira direita
      glutSolidTorus(1, 3, 15, 30); // desenha a roda dianteira direita
    }
    glPopMatrix(); // restaura a matriz de transformação anterior
  }
  glPopMatrix(); // restaura a matriz de transformação anterior

  glutSwapBuffers(); // troca os buffers de exibição
}

void change_cam_view() {
  switch (cam_view) {
    case 0:
      gluLookAt(100, 0, 0, 0, 0, 0, 0, 1, 0);
      break;
    case 1:
      gluLookAt(0, 250, 0, 0, 0, 0, 1, 0, 0);
      break;
    case 2:
      gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);
      break;
  }
}

// configura a visão da câmera
void configView() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // define a cor de fundo

  glViewport(0, 0, 800, 600);

  glMatrixMode(GL_PROJECTION); // define a matriz de projeção
  glLoadIdentity(); // carrega a matriz identidade

  gluPerspective(45, 800 / 600.0, 0.5, 500); // define a perspectiva

  glMatrixMode(GL_MODELVIEW); // define a matriz de modelagem
  glLoadIdentity(); // carrega a matriz identidade

  change_cam_view(); // muda a visão da câmera

  glDisable(GL_DEPTH_TEST);
}


void resize(GLsizei w, GLsizei h) {
  if (h == 0) h = 1;
}


// OBS: estou levando em conta o eixo X
void specialkeys(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      rot_rodas += 5; // rotaciona as rodas para a direita
      rot_rodas = (rot_rodas > 30) ? 30 : rot_rodas;
      break;
    case GLUT_KEY_DOWN:
      rot_rodas -= 5; // rotaciona as rodas para a esquerda
      rot_rodas = (rot_rodas < -30) ? -30 : rot_rodas;
      break;
    case GLUT_KEY_LEFT:
      pos_carro -= 2; // move o carro para trás
      break;
    case GLUT_KEY_RIGHT:
      pos_carro += 2; // move o carro para frente
      break;
  }
  glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      exit(0);
      break;
    case 32:
      cam_view = (++cam_view % 3);
      pos_carro = 0;
      rot_rodas = 0;
      configView();
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Visualizacao 3D");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialkeys);
  configView();
  glutMainLoop();
  return 0;
}
