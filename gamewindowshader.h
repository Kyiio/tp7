#ifndef GAMEWINDOWSHADER_H
#define GAMEWINDOWSHADER_H

#include "openglwindow.h"
#include "Camera.h"
#include "objetply3d.h"

#include <gl/glu.h>
#include <QtGui/QGuiApplication>
#include <QtGui/QOpenGLShaderProgram>

#include <QList>

#define ETE 0
#define AUTOMNE 1
#define HIVER 2
#define PRINTEMPS 3

#define ARBRE_ETE 10
#define ARBRE_AUTOMNE 11
#define ARBRE_HIVER 12
#define ARBRE_PRINTEMPS 13
#define TONNEAU 14

#ifndef STRUCT_QUADTREE
#define STRUCT_QUADTREE
struct quadtree
{
    quadtree * fils1;
    quadtree * fils2;
    quadtree * fils3;
    quadtree * fils4;

    float coord[8];
};
#endif

#ifndef STRUCT_POINT
#define STRUCT_POINT
struct point
{
    float x, y ,z;
};
#endif

#define MAX_PARTICLES 10000

#ifndef TPARTICLE1
#define TPARTICLE1

typedef struct
{
    float x;
    float y;
    float z;
} tParticle1;

#endif

class GameWindowShader : public OpenGLWindow
{
    Q_OBJECT

public slots:
    void update_day();

public:
    GameWindowShader(int fps, Camera* camera, int day = 0);

    void initialize();
    void render();
    bool event(QEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void displayTriangles();
    void displayLines();
    void displayPoints();
    void displayTrianglesTexture();

    void bindTextureRegardingZ(float z);
    void displayColor(float);
    void displayColorSeasons(float);

    void loadMap(QString localPath);

    void initall();
    void initentity(int index);
    void renderMeteo();
    void update();

    void loadTexture2(char *filename, GLuint &textureID);

    int day() const;
    void setDay(int day);

    int type() const;
    void setType(int type);

    Camera *camera() const;
    void setCamera(Camera *camera);

    int getCarte() const;
    void setCarte(int value);

    bool getIsRotating() const;
    void setIsRotating(bool isRotating);

    QList<float> getObjectList() const;
    void setObjectList(const QList<float> &objectList);

    void renderObjectsFace();
    void renderObjectsPoints();

    void division(quadtree* quad, int borneInf_I, int borneSup_I, int borneInf_J, int borneSup_J, int seuil, int taille_min);
    void displayPointsQuadtree(quadtree * quad);
    void displayTriangleQuadtree(quadtree * quad);
    void displayLinesQuadtree(quadtree * quad);
    void callDisplayLinesQuadtree(quadtree * quad);
    void callDisplayPointQuadtree(quadtree * quad);
    void callDisplayTriangleQuadtree(quadtree * quad);
protected:

    quadtree* m_quad;
    int m_taille_min;
    float m_resolution;

    QString titre;

    GLuint m_textureSable;
    GLuint m_textureEau;
    GLuint m_textureEauProfonde;
    GLuint m_textureFeuilleMorte;
    GLuint m_textureMontagne;
    GLuint m_textureNeige;
    GLuint m_textureHerbe;
    GLuint m_normalMap;

    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_programNM;

    ObjetPly3D m_arbreEte;
    ObjetPly3D m_arbreHiver;
    ObjetPly3D m_arbrePrintemps;
    ObjetPly3D m_arbreAutomne;
    ObjetPly3D m_tonneau;


    int m_day;
    int m_type;
    int m_frame;
    int carte=2;
    int m_fps;

    bool m_isRotating;

    //contient pour chaque objet les attributs suivant [type de l'objet, posX, posY, posZ, scale, rotX, rotY, rotZ]
    QList<float> m_objectList;

    QTimer * m_timer_day;
    QTimer * m_timer;

    Camera* m_camera;

    QImage m_image;

    point *p;
    tParticle1 Particles[MAX_PARTICLES];

};


#endif // GAMEWINDOWSHADER_H
