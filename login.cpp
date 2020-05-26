#include "login.h"

Login::Login( QWidget * parent ) : QWidget ( parent )
{

    this->setWindowTitle( "Login" );

    lUser = new QLabel( "Usuario" );
    lPassword = new QLabel( "Contraseña" );

    leUser = new QLineEdit;
    leUser->setPlaceholderText( "Ingrese usuario" );
    lePassword = new QLineEdit;
    lePassword->setPlaceholderText( "Ingrese contraseña" );
    lePassword->setEchoMode( QLineEdit::Password );

    pbEntrar = new QPushButton( "Acceder" );

    layout = new QGridLayout;

    this->setLayout(layout);

    //layout->addWidget(campo,fila,columna,filaspan, columnaspan, alineacion)
    layout->addWidget( lUser, 0, 1);
    layout->addWidget( lPassword ,1, 1);
    layout->addWidget( pbEntrar ,3, 1);

    layout->addWidget( leUser, 0, 2, 1, 1);
    layout->addWidget( lePassword ,1, 2, 1 ,1);

    formulario = new Formulario;
    adminDB = new AdminDB;
    adminDB->conectar( "../db/usuarios.sqlite" );
    adminDB->creats();
    adminDB->registrar( "Aplicación abierta" );
    adminDB->admin("admin","123456");

    connect( pbEntrar, SIGNAL( pressed() ), this, SLOT( slot_entrar() ) );
}

void Login::slot_entrar()
{

    QVector< QStringList > vRegistros = adminDB->select( "SeLEct id, clave, apellido from usuarios" );
    QStringList nombre_apellido = adminDB->validarUsuario( leUser->text(), lePassword->text(), "usuarios" );

    if ( ! nombre_apellido.isEmpty() )
    {
        qDebug() << nombre_apellido.first();
        qDebug() << nombre_apellido.last();

        qDebug() <<
        QMessageBox::information( this, "Usuario valido", "Bienvenido " + nombre_apellido.first()
                                  + nombre_apellido.last() + ". Bienvenido!!!" );
        formulario->show();
        formulario->resize(368,208);
        this->hide();
    }
    else
    {
        leUser->setText( "" );
        lePassword->clear();
        QMessageBox::warning( this, "Intente de nuevo", "Usuario o contraseña invalidos" );
    }
}
