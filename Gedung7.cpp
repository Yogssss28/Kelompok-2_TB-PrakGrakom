#include <GL/freeglut.h>
#include <math.h>

// Variabel untuk rotasi menggunakan mouse
float xrot = 0; // Rotasi di sumbu X
float yrot = 0; // Rotasi di sumbu Y
float xdiff = 0; // Selisih posisi mouse di sumbu X
float ydiff = 0; // Selisih posisi mouse di sumbu Y
bool mouseDown = false; // Status mouse (apakah ditekan atau tidak)

// Variabel untuk pengaturan pencahayaan
GLfloat light_position[] = { 0.0, 20.0, 70.0, 1.0 }; 
// 0.0  -> Koordinat x dari sumber cahaya (posisi horizontal)
// 20.0 -> Koordinat y dari sumber cahaya (posisi vertikal)
// 70.0 -> Koordinat z dari sumber cahaya (kedalaman)
// 1.0  -> Menunjukkan bahwa ini adalah cahaya posisi (bukan cahaya arah)
GLfloat ambient_light[] = { 0.2, 0.2, 0.2, 1.0 }; 
// Parameter:
// 0.2 -> Komponen merah dari cahaya ambient (intensitas cahaya merah)
// 0.2 -> Komponen hijau dari cahaya ambient (intensitas cahaya hijau)
// 0.2 -> Komponen biru dari cahaya ambient (intensitas cahaya biru)
// 1.0 -> Komponen alpha (opasitas), 1.0 berarti sepenuhnya terlihat
GLfloat diffuse_light[] = { 1.0, 1.0, 1.0, 1.0 }; 
// Parameter:
// 1.0 -> Komponen merah dari cahaya diffuse (intensitas cahaya merah)
// 1.0 -> Komponen hijau dari cahaya diffuse (intensitas cahaya hijau)
// 1.0 -> Komponen biru dari cahaya diffuse (intensitas cahaya biru)
// 1.0 -> Komponen alpha (opasitas), 1.0 berarti sepenuhnya terlihat
bool lightingEnabled = true; // Status pencahayaan

// Variabel untuk transformasi objek
float xPOS = 1.0; // Skala sumbu X
float yPOS = 1.0; // Skala sumbu Y
float angle = 0.0; // Sudut rotasi
float translateX = 0.0; // Posisi translasi sumbu X
float translateY = 0.0; // Posisi translasi sumbu Y

bool hidden = false; // Status untuk menampilkan atau menyembunyikan sumbu koordinat

// Deklarasi fungsi untuk menggambar sumbu koordinat
void hiddenCarte();

// Fungsi untuk mengatur ukuran jendela dan proyeksi
void ukur(int lebar, int tinggi) {
    if (tinggi == 0) tinggi = 1; // Menghindari pembagian dengan nol
    glMatrixMode(GL_PROJECTION); // Mengatur mode matriks proyeksi
    glLoadIdentity(); // Mengatur matriks proyeksi ke identitas
    gluPerspective(45, lebar / tinggi, 5, 450); // Mengatur perspektif
    glTranslatef(10, 0, -340); // Menggeser pandangan ke belakang
    glMatrixMode(GL_MODELVIEW); // Kembali ke mode matriks model
}

// Fungsi untuk menggambar sumbu koordinat
void drawCartecius() {
    glColor3f(1.0, 0.0, 0.0); // Mengatur warna garis menjadi merah
    glBegin(GL_LINES); // Memulai menggambar garis
    // Garis sumbu X
    glVertex3f(-150.0, 0.0, 0.0);
    glVertex3f(150.0, 0.0, 0.0);
    // Garis sumbu Y
    glVertex3f(0.0, -150.0, 0.0);
    glVertex3f(0.0, 150.0, 0.0);
    // Garis sumbu Z
    glVertex3f(0.0, 0.0, -150.0);
    glVertex3f(0.0, 0.0, 150.0);
    glEnd(); // Mengakhiri menggambar garis
}

// Fungsi untuk menggambar sumbu koordinat jika status hidden adalah true
void hiddenCarte() {
    if (hidden) {
        drawCartecius(); // Memanggil fungsi untuk menggambar sumbu koordinat
    }
}

// Fungsi untuk inisialisasi pengaturan OpenGL
void myinit(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Mengatur warna latar belakang
    glMatrixMode(GL_PROJECTION); // Mengatur mode matriks proyeksi
    glEnable(GL_DEPTH_TEST); // Mengaktifkan pengujian kedalaman
    glMatrixMode(GL_MODELVIEW); // Kembali ke mode matriks model
    glPointSize(10.0); // Mengatur ukuran titik
    glLineWidth(7.0f); // Mengatur lebar garis
}

// Fungsi idle untuk memperbarui tampilan saat tidak ada interaksi
void idle() {
    if (mouseDown) { // Jika mouse ditekan
        xrot += 0.3; // Menambah rotasi di sumbu X
        yrot += 0.4; // Menambah rotasi di sumbu Y
    }
    glutPostRedisplay(); // Meminta untuk menggambar ulang
}

// Fungsi untuk menangani input dari keyboard
void kunci(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q': // Jika tombol 'q' ditekan
        exit(0); // Keluar dari program
        break;
    case 'l': // Jika tombol 'l' ditekan
        lightingEnabled = !lightingEnabled; // Mengubah status pencahayaan
        if (lightingEnabled) {
            glEnable(GL_LIGHTING); // Mengaktifkan pencahayaan
        } else {
            glDisable(GL_LIGHTING); // Menonaktifkan pencahayaan
        }
        glutPostRedisplay(); // Meminta untuk menggambar ulang
        break;
    case 'a': // Jika tombol 'a' ditekan
        ambient_light[0] += 0.1f; // Meningkatkan intensitas cahaya ambient
        ambient_light[1] += 0.1f;
        ambient_light[2] += 0.1f;
        if (ambient_light[0] > 1.0f) ambient_light[0] = 1.0f; // Membatasi nilai maksimum
        if (ambient_light[1] > 1.0f) ambient_light[1] = 1.0f;
        if (ambient_light[2] > 1.0f) ambient_light[2] = 1.0f;
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light); // Mengatur cahaya ambient
        glutPostRedisplay(); // Meminta untuk menggambar ulang
        break;
    case 'd': // Jika tombol 'd' ditekan
        ambient_light[0] -= 0.1f; // Mengurangi intensitas cahaya ambient
        ambient_light[1] -= 0.1f;
        ambient_light[2] -= 0.1f;
        if (ambient_light[0] < 0.0f) ambient_light[0] = 0.0f; // Membatasi nilai minimum
        if (ambient_light[1] < 0.0f) ambient_light[1] = 0.0f;
        if (ambient_light[2] < 0.0f) ambient_light[2] = 0.0f;
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light); // Mengatur cahaya ambient
        glutPostRedisplay(); // Meminta untuk menggambar ulang
        break;
    case 's': // Jika tombol 's' ditekan
        diffuse_light[0] += 0.1f; // Meningkatkan intensitas cahaya difus
        diffuse_light[1] += 0.1f;
        diffuse_light[2] += 0.1f;
        if (diffuse_light[0] > 1.0f) diffuse_light[0] = 1.0f; // Membatasi nilai maksimum
        if (diffuse_light[1] > 1.0f) diffuse_light[1] = 1.0f;
        if (diffuse_light[2] > 1.0f) diffuse_light[2] = 1.0f;
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light); // Mengatur cahaya difus
        glutPostRedisplay(); // Meminta untuk menggambar ulang
        break;
    case 'f': // Jika tombol 'f' ditekan
        diffuse_light[0] -= 0.1f; // Mengurangi intensitas cahaya difus
        diffuse_light[1] -= 0.1f;
        diffuse_light[2] -= 0.1f;
        if (diffuse_light[0] < 0.0f) diffuse_light[0] = 0.0f; // Membatasi nilai minimum
        if (diffuse_light[1] < 0.0f) diffuse_light[1] = 0.0f;
        if (diffuse_light[2] < 0.0f) diffuse_light[2] = 0.0f;
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light); // Mengatur cahaya difus
        glutPostRedisplay(); // Meminta untuk menggambar ulang
        break;
    case 'r': // Jika tombol 'r' ditekan
        xPOS += 0.1; // Memperbesar skala sumbu X
        break;
    case 't': // Jika tombol 't' ditekan
        xPOS -= 0.1; // Memperkecil skala sumbu X
        break;
    case 'y': // Jika tombol 'y' ditekan
        yPOS += 0.1; // Memperbesar skala sumbu Y ```cpp
        break;
    case 'u': // Jika tombol 'u' ditekan
        yPOS -= 0.1; // Memperkecil skala sumbu Y
        break;
    case 'i': // Jika tombol 'i' ditekan
        angle += 5.0; // Rotasi 5 derajat ke kanan
        break;
    case 'o': // Jika tombol 'o' ditekan
        angle -= 5.0; // Rotasi 5 derajat ke kiri
        break;
    case 'p': // Jika tombol 'p' ditekan
        translateY += 1.0; // Translasi 1 unit ke atas
        break;
    case 'k': // Jika tombol 'k' ditekan
        translateY -= 1.0; // Translasi 1 unit ke bawah
        break;
    case 'n': // Jika tombol 'n' ditekan
        translateX -= 1.0; // Translasi 1 unit ke kiri
        break;
    case 'm': // Jika tombol 'm' ditekan
        translateX += 1.0; // Translasi 1 unit ke kanan
        break;
    case 'c': // Jika tombol 'c' ditekan
        hidden = !hidden; // Mengubah status untuk menampilkan atau menyembunyikan sumbu koordinat
        break;
    }
    glutPostRedisplay(); // Meminta untuk menggambar ulang
}

// Fungsi untuk menangani interaksi mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // Jika tombol kiri mouse ditekan
        mouseDown = true; // Menandai bahwa mouse sedang ditekan
        xdiff = x - yrot; // Menghitung selisih posisi mouse di sumbu X
        ydiff = y - xrot; // Menghitung selisih posisi mouse di sumbu Y
    } else {
        mouseDown = false; // Menandai bahwa mouse tidak ditekan
    }
}

// Fungsi untuk menangani gerakan mouse
void mouseMotion(int x, int y) {
    if (mouseDown) { // Jika mouse sedang ditekan
        yrot = x - xdiff; // Mengatur rotasi di sumbu Y berdasarkan gerakan mouse
        xrot = y - ydiff; // Mengatur rotasi di sumbu X berdasarkan gerakan mouse
        glutPostRedisplay(); // Meminta untuk menggambar ulang
    }
}

// Fungsi untuk inisialisasi pengaturan OpenGL
void inisialisasi() {
    glEnable(GL_DEPTH_TEST); // Mengaktifkan pengujian kedalaman
    glEnable(GL_COLOR_MATERIAL); // Mengaktifkan material warna
    glClearColor(0.1, 0.1, 0.1, 1.0); // Mengatur warna latar belakang

    glEnable(GL_LIGHTING); // Mengaktifkan pencahayaan
    glEnable(GL_LIGHT0); // Mengaktifkan sumber cahaya 0
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Mengatur posisi cahaya
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light); // Mengatur cahaya ambient
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light); // Mengatur cahaya difus
}

void DrawCube(float x, float y, float z){
    glPushMatrix();
    glScalef(x,y,z);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawBuilding() {
 //==========================MENGGAMBAR GEDUNG==============================   
    glColor3f(0.53f, 0.81f, 0.92f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(0.0, -10.0, -5.0); // Posisi dasar gedung
    glScalef(70.0, 80.0, 50.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//==========================================================================

//==========================MENGGAMBAR ATAP GEDUNG==============================
    glColor3f(1.0f, 1.0f, 1.0f);// Mengatur warna atap
    glPushMatrix();
    glTranslatef(0.0, 35.0, -5.0); // Posisi atap
    glScalef(70.0, 10.0, 50.0); // Skala atap
    glutSolidCube(1.0); // Menggambar atap
    glPopMatrix();

//==========================MENGGAMBAR JENDELA==============================
    //menggambar jendela atas kiri
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-23.0, 20.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //menggambar jendela tengah kiri
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-23.0, 0.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //menggambar jendela bawah kiri
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-23.0, -20.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//========================================================

    //menggambar jendela tengah kiri 1 atas 
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-9.0, 20.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //menggambar jendela tengah kiri 1 tengah 
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-9.0, 0.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //menggambar jendela tengah kiri 1 Tengah
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-9.0, -20.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//========================================================

//menggambar jendela tengah bawah kanan
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(6.0, -20.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

//menggambar jendela tengah kanan 
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(6.0, 0.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

//menggambar jendela tengah atas kanan 
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(6.0, 20.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//========================================================

//menggambar jendela atas kanan 2
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(22.0, 20.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

//menggambar jendela tengah kanan 2
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(22.0, 0.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

//menggambar jendela tengah kanan 2
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(22.0, -20.0, 2.0); // Posisi dasar gedung
    glScalef(7.0, 10.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

//=========================================================================

//========================PINTU GEDUNG====================================
    //menggambar pintu gedung
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(0.0, -42.0, 1.0); // Posisi dasar gedung
    glScalef(25.0, 15.0, 39.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//=========================================================================

//========================PEMISAH PINTU====================================
    //pemisah pintu tengah
    glColor3f(0.0f, 0.0f, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(0.0, -42.0, 1.0); // Posisi dasar gedung
    glScalef(2.0, 15.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //pemisah kiri
    glColor3f(0.0f, 0.0f, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-13.0, -42.0, 1.0); // Posisi dasar gedung
    glScalef(2.0, 15.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //pemisah pintu kanan
    glColor3f(0.0f, 0.0f, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(13.0, -42.0, 1.0); // Posisi dasar gedung
    glScalef(2.0, 15.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //pemisah pintu atas
    glColor3f(0.0f, 0.0f, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(0.0, -35.0, 1.0); // Posisi dasar gedung
    glScalef(25.0, 2.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//=========================================================================

//========================GAGANG PINTU=======================================
    //gagang pintu kanan
    glColor3f(0.0f, 0.0f, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(3.0, -44.0, 1.0); // Posisi dasar gedung
    glScalef(2.0, 2.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //gagang pintu kiri
    glColor3f(0.0f, 0.0f, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-3.0, -44.0, 1.0); // Posisi dasar gedung
    glScalef(2.0, 2.0, 40.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

//=========================================================================    
//========================HALAMAN==========================================
    //menggambar halaman
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-5.0, -60.0, 2.0); // Posisi dasar gedung
    glScalef(180.0, 10.0, 160.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//========================================================================= 
//========================LANTAI GEDUNG====================================
    //menggambar lantai gedung
    glColor3f(0.0f, 0.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-5.0, -52.0, 2.0); // Posisi dasar gedung
    glScalef(120.0, 3.0, 100.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//========================================================================= 
//======================MEMBUAT JALAN =====================================
    //jalan 1
    glColor3f(0.0f, 0.0F, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-5.0, -55.0, 66.0); // Posisi dasar gedung
    glScalef(180.0, 3.0, 31.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //jalan 2
    glColor3f(0.0f, 0.0F, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(65.0, -55.0, 1.0); // Posisi dasar gedung
    glScalef(30.0, 3.0, 160.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //jalan 3
    glColor3f(0.0f, 0.0F, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-5.0, -55.0, -63.0); // Posisi dasar gedung
    glScalef(170.0, 3.0, 31.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //jalan 4   
    glColor3f(0.0f, 0.0F, 0.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-80.0, -55.0, 1.0); // Posisi dasar gedung
    glScalef(30.0, 3.0, 160.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//===========================================================

//======================GARIS JALAN=================================
    //garis jalan 1
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-85.0, -54.0, 70.0); // Posisi dasar gedung
    glScalef(20.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 2
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-55.0, -54.0, 70.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 3
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-30.0, -54.0, 70.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 4
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-5.0, -54.0, 70.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 5
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(20.0, -54.0, 70.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 6
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(45.0, -54.0, 70.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 7
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(65.0, -54.0, 70.0); // Posisi dasar gedung
    glScalef(10.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 8
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(70.0, -54.0, 65.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 15.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 9
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(70.0, -54.0, 43.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 14.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 10
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(70.0, -54.0, 20.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 15.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 11
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(70.0, -54.0, -3.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 15.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 12
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(70.0, -54.0, -26.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 15.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 13
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(70.0, -54.0, -54.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 20.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 14
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(66.0, -54.0, -64.0); // Posisi dasar gedung
    glScalef(12.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 15
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(46.0, -54.0, -64.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
    
    //garis jalan 16
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(20.0, -54.0, -64.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 17
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-5.0, -54.0, -64.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 18
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-30.0, -54.0, -64.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 19
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-55.0, -54.0, -64.0); // Posisi dasar gedung
    glScalef(15.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 20
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-78.0, -54.0, -64.0); // Posisi dasar gedung
    glScalef(10.0, 3.0, 5.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 21
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-80.0, -54.0, 20.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 15.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

     //garis jalan 22
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-80.0, -54.0, 65.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 13.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 23
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-80.0, -54.0, 43.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 15.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 24
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-80.0, -54.0, -3.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 15.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 25
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-80.0, -54.0, -26.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 15.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //garis jalan 26
    glColor3f(1.0f, 1.0F, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-80.0, -54.0, -54.0); // Posisi dasar gedung
    glScalef(5.0, 3.0, 20.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//============================================================

//======================Lobby=================================
    //paragi ngiuhan
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(0.0, -30.0, 25.0); // Posisi dasar gedung
    glScalef(35.0, 5.0, 30.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //tiang 1
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(15.0, -40.0, 38.0); // Posisi dasar gedung
    glScalef(2.0, 25.0, 2.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //tiang 2
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-15.0, -40.0, 38.0); // Posisi dasar gedung
    glScalef(2.0, 25.0, 2.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
//=======================================================
//======================benteng=================================
    //benteng 1
    glColor3f(0.53f, 0.81f, 0.92f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(85.0, -25.0, 1.0); // Posisi dasar gedung
    glScalef(10.0, 80.0, 170.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //benteng 2
    glColor3f(0.53f, 0.81f, 0.92f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-3.0, -25.0, -80.0); // Posisi dasar gedung
    glScalef(185.0, 80.0, 10.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //benteng 3
    glColor3f(0.53f, 0.81f, 0.92f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-100.0, -25.0, -60.0); // Posisi dasar gedung
    glScalef(10.0, 80.0, 50.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //benteng 4
    glColor3f(0.53f, 0.81f, 0.92f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-8.0, -25.0, 85.0); // Posisi dasar gedung
    glScalef(195.0, 80.0, 10.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

    //benteng 5
    glColor3f(0.53f, 0.81f, 0.92f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-100.0, -25.0, 25.0); // Posisi dasar gedung
    glScalef(10.0, 80.0, 20.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
    
    //benteng 6
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-100.0, 10.0, -10.0); // Posisi dasar gedung
    glScalef(10.0, 10.0, 50.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();

     //benteng 7
    glColor3f(1.0f, 1.0f, 1.0f); // Mengatur warna gedung
    glPushMatrix();
    glTranslatef(-100.0, 10.0, 60.0); // Posisi dasar gedung
    glScalef(10.0, 10.0, 50.0); // Skala gedung
    glutSolidCube(1.0); // Menggambar gedung
    glPopMatrix();
    
}
// Fungsi untuk menggambar tampilan
void tampilan(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Menghapus buffer warna dan kedalaman
    glLoadIdentity(); // Mengatur matriks model ke identitas
    // Translasi
    glTranslatef(translateX, translateY, 0.0); // Menggeser objek
    // Rotasi
    glRotatef(angle, 0.0, 0.0, 1.0); // Rotasi di sekitar sumbu Z
    // Skala
    glScalef(xPOS, yPOS, 1.0); // Mengatur skala objek

    gluLookAt(0, 0, -3, 
              0, 0, -5, 
              0, 1, 0); // Mengatur posisi kamera

    glRotatef(xrot, 1, 0, 0); // Rotasi berdasarkan input mouse di sumbu X
    glRotatef(yrot, 0, 1, 0); // Rotasi berdasarkan input mouse di sumbu Y

    glPushMatrix(); // Menyimpan matriks saat ini
    hiddenCarte(); // Menggambar sumbu koordinat jika diperlukan

//=====================================================

// Menggambar kursi 1 taman
glBegin(GL_POLYGON); // Sandaran kursi
glColor3f(1.0f, 0.5f, 0.0f); // Mengatur warna coklat
glVertex3f(-40, -45, 15);
glVertex3f(-50, -45, 15);
glVertex3f(-50, -50, 15);
glVertex3f(-40, -50, 15);
glEnd();

glBegin(GL_POLYGON); // Alas kursi/tempat duduk
glColor3f(1.0f, 0.5f, 0.0f); // Mengatur warna coklat
glVertex3f(-40, -47, 15);
glVertex3f(-50, -47, 15);
glVertex3f(-50, -47, 12);
glVertex3f(-40, -47, 12);
glEnd();

glBegin(GL_POLYGON); // Kaki-kaki kursi
glColor3f(1.0f, 0.5f, 0.0f); // Mengatur warna coklat
glVertex3f(-40, -47, 12);
glVertex3f(-50, -47, 12);
glVertex3f(-50, -50, 12);
glVertex3f(-40, -50, 12);
glEnd();

// Menggambar kursi 2
glBegin(GL_POLYGON); // Sandaran kursi
glColor3f(1.0f, 0.5f, 0.0f); // Mengatur warna coklat
glVertex3f(-40, -45, 0);
glVertex3f(-50, -45, 0);
glVertex3f(-50, -50, 0);
glVertex3f(-40, -50, 0);
glEnd();

glBegin(GL_POLYGON); // Alas meja
glColor3f(1.0f, 0.5f, 0.0f); // Mengatur warna coklat
glVertex3f(-40, -47, 3);
glVertex3f(-50, -47, 3);
glVertex3f(-50, -50, 3);
glVertex3f(-40, -50, 3);
glEnd();

glBegin(GL_POLYGON); // Kaki-kaki meja
glColor3f(1.0f, 0.5f, 0.0f); // Mengatur warna coklat
glVertex3f(-40, -47, 3);
glVertex3f(-50, -47, 3);
glVertex3f(-50, -47, 0);
glVertex3f(-40, -47, 0);
glEnd();

// Menggambar meja taman samping gedung
glBegin(GL_POLYGON);
glColor3f(1.0f, 0.5f, 0.0f); // Mengatur warna coklat
glVertex3f(-40, -47, 10);
glVertex3f(-50, -47, 10);
glVertex3f(-50, -50, 10);
glVertex3f(-40, -50, 10);
glEnd();

glBegin(GL_POLYGON); // Kiri meja
glColor3f(1.0f, 0.5f, 0.0f); // Mengatur warna coklat
glVertex3f(-40, -47, 5);
glVertex3f(-50, -47, 5);
glVertex3f(-50, -50, 5);
glVertex3f(-40, -50, 5);
glEnd(); 

glBegin(GL_POLYGON); // Alas meja
glColor3f(1.0f, 0.5f, 0.0f); // Mengatur warna coklat
glVertex3f(-40, -47, 5);
glVertex3f(-50, -47, 5);
glVertex3f(-50, -47, 10);
glVertex3f(-40, -47, 10);
glEnd();
drawBuilding();

glPushMatrix(); // Menyimpan matriks saat ini
glPopMatrix(); // Mengembalikan matriks yang disimpan
glutSwapBuffers(); // Menukar buffer untuk menampilkan hasil
}

// Fungsi utama
int main(int argc, char **argv){
    glutInit(&argc, argv); // Inisialisasi GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Mengatur mode tampilan
    glutInitWindowPosition(260, 20); // Mengatur posisi jendela
    glutInitWindowSize(800, 650); // Mengatur ukuran jendela
    glutCreateWindow("GEDUNG 3D"); // Membuat jendela dengan judul

    myinit(); // Memanggil fungsi inisialisasi

    glutDisplayFunc(tampilan); // Mengatur fungsi tampilan
    glutKeyboardFunc(kunci); // Mengatur fungsi keyboard
    glutMouseFunc(mouse); // Mengatur fungsi mouse
    glutMotionFunc(mouseMotion); // Mengatur fungsi gerakan mouse
    glutReshapeFunc(ukur); // Mengatur fungsi perubahan ukuran jendela
    inisialisasi(); // Memanggil fungsi inisialisasi OpenGL
    glutMainLoop(); // Memasuki loop utama GLUT
    drawBuilding();
}