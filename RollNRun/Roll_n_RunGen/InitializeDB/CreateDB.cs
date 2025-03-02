
/*PROTECTED REGION ID(CreateDB_imports) ENABLED START*/
using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlClient;
using System.Data;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;

/*PROTECTED REGION END*/
namespace InitializeDB
{
public class CreateDB
{
public static void Create (string databaseArg, string userArg, string passArg)
{
        String database = databaseArg;
        String user = userArg;
        String pass = passArg;

        // Conex DB
        SqlConnection cnn = new SqlConnection (@"Server=(local)\sqlexpress; database=master; integrated security=yes");

        // Order T-SQL create user
        String createUser = @"IF NOT EXISTS(SELECT name FROM master.dbo.syslogins WHERE name = '" + user + @"')
            BEGIN
                CREATE LOGIN ["                                                                                                                                     + user + @"] WITH PASSWORD=N'" + pass + @"', DEFAULT_DATABASE=[master], CHECK_EXPIRATION=OFF, CHECK_POLICY=OFF
            END"                                                                                                                                                                                                                                                                                    ;

        //Order delete user if exist
        String deleteDataBase = @"if exists(select * from sys.databases where name = '" + database + "') DROP DATABASE [" + database + "]";
        //Order create databas
        string createBD = "CREATE DATABASE " + database;
        //Order associate user with database
        String associatedUser = @"USE [" + database + "];CREATE USER [" + user + "] FOR LOGIN [" + user + "];USE [" + database + "];EXEC sp_addrolemember N'db_owner', N'" + user + "'";
        SqlCommand cmd = null;

        try
        {
                // Open conex
                cnn.Open ();

                //Create user in SQLSERVER
                cmd = new SqlCommand (createUser, cnn);
                cmd.ExecuteNonQuery ();

                //DELETE database if exist
                cmd = new SqlCommand (deleteDataBase, cnn);
                cmd.ExecuteNonQuery ();

                //CREATE DB
                cmd = new SqlCommand (createBD, cnn);
                cmd.ExecuteNonQuery ();

                //Associate user with db
                cmd = new SqlCommand (associatedUser, cnn);
                cmd.ExecuteNonQuery ();

                System.Console.WriteLine ("DataBase create sucessfully..");
        }
        catch (Exception ex)
        {
                throw ex;
        }
        finally
        {
                if (cnn.State == ConnectionState.Open) {
                        cnn.Close ();
                }
        }
}

public static void InitializeData ()
{
        /*PROTECTED REGION ID(initializeDataMethod) ENABLED START*/
        try
        {
                int i = 0;
                /*
                 * //USUARIOS
                 * UsuarioCEN usuarioCEN = new UsuarioCEN ();
                 * int id_usu = usuarioCEN.New_ (p_nombre: "Yo", p_email: "yo@gmail.com", p_apellidos: "Yomismo", p_nickname: "Mimismo1", p_pass: "Aguacate88#", p_rol: RolEnum.usuario_base, p_imagen: "Imagen");
                 * int id_usu2 = usuarioCEN.New_ (p_nombre: "Tu", p_email: "tu@gmail.com", p_apellidos: "Tumismo", p_nickname: "Mimismo2", p_pass: "1234", p_rol: RolEnum.administrador, p_imagen: "Imagen");
                 * int id_usu3 = usuarioCEN.New_ (p_nombre: "El", p_email: "el@gmail.com", p_apellidos: "Elmismo", p_nickname: "Mimismo3", p_pass: "1234", p_rol: RolEnum.usuario_base, p_imagen: "Imagen");
                 * int id_usu4 = usuarioCEN.New_ (p_nombre: "Nosotros", p_email: "nosotros@gmail.com", p_apellidos: "Nosotrosmismos", p_nickname: "Mimismo4", p_pass: "1234", p_rol: RolEnum.administrador, p_imagen: "Imagen");
                 * int id_usu5 = usuarioCEN.New_ (p_nombre: "Vosotros", p_email: "vosotros@gmail.com", p_apellidos: "Vosotrosmismos", p_nickname: "Mimismo5", p_pass: "1234", p_rol: RolEnum.usuario_base, p_imagen: "Imagen");
                 *
                 * //LOGIN usuario
                 * Console.WriteLine ("-------------COMPROBACION DEL LOGIN-------------");
                 * Console.WriteLine ();
                 * if (usuarioCEN.Login ("yo@gmail.com", "Aguacate88#") != null) {
                 *      Console.WriteLine ("El Login es correcto");
                 *      Console.WriteLine ();
                 * }
                 *
                 * //TARJETAS
                 * TarjetaCEN tarjetaCEN = new TarjetaCEN ();
                 * tarjetaCEN.New_ ("Yo Yomismo", "12341234", "123", new DateTime (2023, 1, 1), id_usu);
                 * tarjetaCEN.New_ ("Tu Tumismo", "98769876", "123", new DateTime (2023, 1, 2), id_usu);
                 * tarjetaCEN.New_ ("El Elmismo", "12986745", "123", new DateTime (2023, 1, 3), id_usu3);
                 * tarjetaCEN.New_ ("Nosotros Nosotrosmismos", "98765432", "123", new DateTime (2023, 1, 4), id_usu4);
                 * tarjetaCEN.New_ ("Vosotros Vosotrosmismos", "51369251", "123", new DateTime (2023, 1, 5), id_usu5);
                 *
                 * //DIRECCIONES
                 * DireccionCEN direccionCEN = new DireccionCEN ();
                 * direccionCEN.New_ ("Alicante", "Alcoy", "03803", "Odio existir", id_usu);
                 * direccionCEN.New_ ("Alicante", "Elche", "03205", "Tampoco es para tanto", id_usu2);
                 * direccionCEN.New_ ("Alicante", "Alicante", "03103", "Que si que si", id_usu3);
                 * direccionCEN.New_ ("Alicante", "Elda", "03603", "Va alegrate", id_usu4);
                 * direccionCEN.New_ ("Alicante", "Petrer", "03608", "Es verdad tienes razon", id_usu5);
                 *
                 */

                //PRODUCTOS
                ProductoCEN productoCEN = new ProductoCEN ();
                int id_producto = productoCEN.New_ ("Juego de Dados D&D", "Hasbro", 270, 10.59, "/Images/Uploads/dice.png", "El mejor set de dados que puedes encontrarte para fardar ante tus compañeros de rol y sacar las mejores tiradas", 0, Tipo_productoEnum.dado, 0);
                int id_producto2 = productoCEN.New_ ("Minis D&D", "3DMaxim", 300, 20.99, "/Images/Uploads/figure.png", "Figura de tus personajes favoritos", 0, Tipo_productoEnum.figura, 0);
                int id_producto3 = productoCEN.New_ ("Juego de Cartas Bang", "Bang", 305, 25.99, "/Images/Uploads/card_game.png", "El nuevo juego de cartas de Marca 2", 0, Tipo_productoEnum.juego_cartas, 0);
                int id_producto4 = productoCEN.New_ ("Resident Evil 2 the Board Game", "Capcom", 400, 42.99, "/Images/Uploads/board_game.png", "Preparate para noches divertidas con tus amigos y pasar el peor miedo", 0, Tipo_productoEnum.juego_mesa, 0);
                int id_producto5 = productoCEN.New_ ("Manual D&D 5E", "Hasbro", 403, 32.99, "/Images/Uploads/book.png", "Manual del Dungeon Master D&D 5E, perfecto para empezar en el mundo del rol.", 0, Tipo_productoEnum.libro, 0);
                int id_producto6 = productoCEN.New_ ("Colmillos Vampiro", "Marca Blanca", 600, 3.99, "/Images/Uploads/other.png", "Colmillos falsos de vampiro para Halloween o jugar a Vampiro: La Mascarada", 0, Tipo_productoEnum.otros, 0);
                int id_producto7 = productoCEN.New_ ("Dados d6", "Marca Blanca", 270, 2.99, "/Images/Sin_Imagen.png", "Chulisimos dados de seis caras y bonitos a mas no poder", 0, Tipo_productoEnum.dado, 0);
                int id_producto8 = productoCEN.New_ ("Figura 1", "Marca 1", 300, 20.99, "/Images/Uploads/figure.png", "Figura de tus personajes favoritos", 0, Tipo_productoEnum.figura, 0);
                int id_producto9 = productoCEN.New_ ("Juego de Cartas 1", "Marca 2", 305, 25.99, "/Images/Uploads/card_game.png", "El nuevo juego de cartas de Marca 2", 0, Tipo_productoEnum.juego_cartas, 0);
                productoCEN.New_ ("Juego de Mesa 1", "Marca 3", 400, 42.99, "/Images/Uploads/board_game.png", "Preparate para noches divertidas con tus amigos", 0, Tipo_productoEnum.juego_mesa, 0);
                productoCEN.New_ ("Manual D&D 1", "Marca 4", 403, 32.99, "/Images/Sin_Imagen.png", "Manual del Dungeon Master D&D 5E", 0, Tipo_productoEnum.libro, 0);
                productoCEN.New_ ("Colmillos Vampiro 1", "Marca 5", 600, 1.99, "/Images/Uploads/other.png", "Colmillos falsos de vampiro", 0, Tipo_productoEnum.otros, 0);
                productoCEN.New_ ("Dados d6 nuevos", "Marca Blanca", 270, 2.99, "/Images/Sin_Imagen.png", "Chulisimos dados de seis caras y bonitos a mas no poder", 0, Tipo_productoEnum.dado, 0);
                productoCEN.New_ ("Figura 2", "Marca 1", 300, 20.99, "/Images/Uploads/figure.png", "Figura de tus personajes favoritos", 0, Tipo_productoEnum.figura, 0);
                productoCEN.New_ ("Juego de Cartas 2", "Marca 2", 305, 25.99, "/Images/Uploads/card_game.png", "El nuevo juego de cartas de Marca 2", 0, Tipo_productoEnum.juego_cartas, 0);
                productoCEN.New_ ("Juego de Mesa 2", "Marca 3", 400, 42.99, "/Images/Uploads/board_game.png", "Preparate para noches divertidas con tus amigos", 0, Tipo_productoEnum.juego_mesa, 0);
                productoCEN.New_ ("Manual D&D 3", "Marca 4", 403, 32.99, "/Images/Sin_Imagen.png", "Manual del Dungeon Master D&D 5E", 0, Tipo_productoEnum.libro, 0);
                productoCEN.New_ ("Colmillos Vampiro 2", "Marca 5", 600, 1.99, "/Images/Uploads/other.png", "Colmillos falsos de vampiro", 0, Tipo_productoEnum.otros, 0);
                productoCEN.New_ ("Dados d6 segunda mano", "Marca Blanca", 270, 2.99, "/Images/Sin_Imagen.png", "Chulisimos dados de seis caras y bonitos a mas no poder", 0, Tipo_productoEnum.dado, 0);
                productoCEN.New_ ("Figura 3", "Marca 1", 300, 20.99, "/Images/Uploads/figure.png", "Figura de tus personajes favoritos", 0, Tipo_productoEnum.figura, 0);
                productoCEN.New_ ("Juego de Cartas 3", "Marca 2", 305, 25.99, "/Images/Uploads/card_game.png", "El nuevo juego de cartas de Marca 2", 0, Tipo_productoEnum.juego_cartas, 0);
                productoCEN.New_ ("Juego de Mesa 3", "Marca 3", 400, 42.99, "/Images/Uploads/board_game.png", "Preparate para noches divertidas con tus amigos", 0, Tipo_productoEnum.juego_mesa, 0);
                productoCEN.New_ ("Manual D&D 4", "Marca 4", 403, 32.99, "/Images/Sin_Imagen.png", "Manual del Dungeon Master D&D 5E", 0, Tipo_productoEnum.libro, 0);
                productoCEN.New_ ("Colmillos Vampiro 3", "Marca 5", 600, 1.99, "/Images/Uploads/other.png", "Colmillos falsos de vampiro", 0, Tipo_productoEnum.otros, 0);

                productoCEN.CambiarOferta (id_producto, 20);
                productoCEN.CambiarOferta (id_producto2, 10);
                productoCEN.CambiarOferta (id_producto3, 40);
                productoCEN.CambiarOferta (id_producto4, 50);
                productoCEN.CambiarOferta (id_producto5, 10);
                productoCEN.CambiarOferta (id_producto6, 5);
                productoCEN.CambiarOferta (id_producto7, 30);
                productoCEN.CambiarOferta (id_producto8, 90);
                productoCEN.CambiarOferta (id_producto9, 75);
                /*
                 * //PEDIDOS
                 * PedidoCEN pedidoCEN = new PedidoCEN ();
                 * int id_pedido = pedidoCEN.New_ (new DateTime (2023, 1, 1), "Sigo igual", id_usu);
                 * int id_pedido2 = pedidoCEN.New_ (new DateTime (2023, 1, 2), "Calle Falsa 123", id_usu);
                 * int id_pedido3 = pedidoCEN.New_ (new DateTime (2023, 1, 3), "Calle Real 321", id_usu);
                 * int id_pedido4 = pedidoCEN.New_ (new DateTime (2023, 1, 4), "IES Carrus", id_usu);
                 * int id_pedido5 = pedidoCEN.New_ (new DateTime (2023, 1, 5), "No se donde estoy", id_usu);
                 * int id_pedido6 = pedidoCEN.New_ (new DateTime (2023, 1, 6), "Sigo andando", id_usu);
                 *
                 *
                 *
                 * //LINEAS DE PEDIDO
                 * LineaPedidoCP lineaPedidoCP = new LineaPedidoCP ();
                 * lineaPedidoCP.New_ (3, id_pedido, id_producto);
                 * lineaPedidoCP.New_ (2, id_pedido, id_producto2);
                 * lineaPedidoCP.New_ (5, id_pedido3, id_producto3);
                 * lineaPedidoCP.New_ (1, id_pedido4, id_producto4);
                 * lineaPedidoCP.New_ (2, id_pedido5, id_producto5);
                 * lineaPedidoCP.New_ (3, id_pedido6, id_producto6);
                 *
                 *
                 * //FACTURAS
                 * FacturaCP facturaCP = new FacturaCP ();
                 * facturaCP.New_ (new DateTime (2023, 1, 4), id_pedido);
                 * facturaCP.New_ (new DateTime (2023, 1, 5), id_pedido2);
                 * facturaCP.New_ (new DateTime (2023, 1, 6), id_pedido3);
                 * facturaCP.New_ (new DateTime (2023, 1, 7), id_pedido4);
                 * facturaCP.New_ (new DateTime (2023, 1, 8), id_pedido5);
                 * facturaCP.New_ (new DateTime (2023, 1, 9), id_pedido6);
                 *
                 * //VALORACIONES
                 * ValoracionCP valoracionCP = new ValoracionCP ();
                 * valoracionCP.New_ (3, "Pues esta bastante bien", id_producto, id_usu);
                 * valoracionCP.New_ (2, "Pues esta bastante bien", id_producto, id_usu2);
                 * valoracionCP.New_ (5, "Pues esta bastante bien", id_producto, id_usu3);
                 * valoracionCP.New_ (3, "Pues esta bastante bien", id_producto2, id_usu);
                 * valoracionCP.New_ (1, "Pues esta bastante bien", id_producto2, id_usu2);
                 * valoracionCP.New_ (5, "Pues esta bastante bien", id_producto2, id_usu3);
                 * valoracionCP.New_ (4, "Pues esta bastante bien", id_producto2, id_usu4);
                 *
                 * //SUBFOROS
                 * SubforoCEN subforoCEN = new SubforoCEN ();
                 * int id_subforo = subforoCEN.New_ (id_usu, "Mesa cuadrada para flexear de personaje 1", new DateTime (2022, 10, 25), "Pues eso, que se habla de cosas de rol", 3); // El numero de comentarios esta por cambiar a falta de confirmacion
                 * int id_subforo2 = subforoCEN.New_ (id_usu, "Mesa cuadrada para flexear de personaje 2", new DateTime (2022, 10, 25), "Pues eso, que se habla de cosas de rol", 3);
                 * int id_subforo3 = subforoCEN.New_ (id_usu2, "Mesa cuadrada para flexear de personaje 3", new DateTime (2022, 10, 25), "Pues eso, que se habla de cosas de rol", 3);
                 * int id_subforo4 = subforoCEN.New_ (id_usu2, "Mesa cuadrada para flexear de personaje 4", new DateTime (2022, 10, 25), "Pues eso, que se habla de cosas de rol", 3);
                 *
                 * //ENTRADAS
                 * EntradaCP entradaCP = new EntradaCP ();
                 * entradaCP.New_ (id_subforo, id_usu2, "Que si que no me apetece pensar1.");
                 * entradaCP.New_ (id_subforo, id_usu, "Que si que no me apetece pensar 2.");
                 * entradaCP.New_ (id_subforo, id_usu3, "Que si que no me apetece pensar 3.");
                 * entradaCP.New_ (id_subforo2, id_usu, "Que si que no me apetece pensar 4.");
                 * entradaCP.New_ (id_subforo3, id_usu2, "Que si que no me apetece pensar 5.");
                 * entradaCP.New_ (id_subforo2, id_usu3, "Que si que no me apetece pensar 6.");
                 *
                 * //DEVOLUCIONES
                 * DevolucionCEN devolucionCEN = new DevolucionCEN ();
                 * devolucionCEN.New_ ("Estos no son los dados que pedi", Motivo_DevolucionEnum.producto_incorrecto, id_pedido, id_usu);
                 * devolucionCEN.New_ ("No me gusta, cambialo", Motivo_DevolucionEnum.otros, id_pedido2, id_usu);
                 */
                //PREGUNTAS FRECUENTES
                PreguntaFrecuenteCEN preguntaFrecuenteCEN = new PreguntaFrecuenteCEN ();
                preguntaFrecuenteCEN.New_ ("¿Cómo creo un subforo?", "Puedes acceder al Foro desde la barra superior de la página y en esa página encontrarás la opción de crearlo.");
                preguntaFrecuenteCEN.New_ ("¿Por qué mi pedido aún no ha llegado?", "Si su pedido fue procesado tiene derecho a solicitar una Devolución si eso es lo que desea.");
                preguntaFrecuenteCEN.New_ ("¿Por qué un producto ha cambiado de precio?", "Porque contamos con un grupo de Marketing que se dedica a ofrecer las mejores Ofertas.");
                preguntaFrecuenteCEN.New_ ("¿Necesito estar registrado para algo?", "Si lo que te propones es comprar o interactuar en nuestros subforos deberás registrarte.");
                /*
                 * //DESEOS USUARIO
                 * productoCEN.MarcarDeseado (id_producto, new List<int> { id_usu });
                 *
                 * //ESTADOS EN PROCESO
                 * pedidoCEN.CambiarEstado (id_pedido, EstadoEnum.enProceso);
                 */

                /*
                 * PedidoEN pedidoEN = null;
                 *
                 * //CUSTOM
                 *
                 * Console.WriteLine ("-------------COMPROBACIONES DE LOS CUSTOM-------------");
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * ProductoEN prodEN = new ProductoCAD ().ReadOIDDefault (id_producto);
                 * PedidoEN pedEN = new PedidoCAD ().ReadOIDDefault (id_pedido);
                 *
                 * Console.WriteLine ("Stock inicial: " + prodEN.Stock);
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("-------------Metodo restar stock-------------");
                 *
                 * try
                 * {
                 *      productoCEN.RestarStock (id_producto, 23);
                 * }
                 * catch (Exception e)
                 * {
                 *      System.Console.WriteLine (e.Message);
                 * }
                 *
                 * prodEN = new ProductoCAD ().ReadOIDDefault (id_producto);
                 *
                 * Console.WriteLine ("Stock restado(23): " + prodEN.Stock);
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("-------------Metodo sumar stock-------------");
                 * productoCEN.SumarStock (id_producto, 47);
                 * prodEN = new ProductoCAD ().ReadOIDDefault (id_producto);
                 * Console.WriteLine ("Stock sumado(47): " + prodEN.Stock);
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("-------------Metodo comprobar stock-------------");
                 * Console.WriteLine ("¿Hay 2021 de Stock? " + productoCEN.HayStock (id_producto, 2201));
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("¿Hay 21 de Stock? " + productoCEN.HayStock (id_producto, 21));
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("-------------Metodo cambio oferta-------------");
                 *
                 * Console.WriteLine ("La oferta actual del producto es: " + prodEN.Oferta);
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a intentar cambiar la oferta del producto a 20");
                 * productoCEN.CambiarOferta (id_producto, 20);
                 * prodEN = new ProductoCAD ().ReadOIDDefault (id_producto);
                 * Console.WriteLine ("La oferta actual del producto es: " + prodEN.Oferta);
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("-------------Metodo cambiar estado-------------");
                 * Console.WriteLine ("El estado actual del pedido es: " + pedEN.Estado);
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a intentar cambiar el estado del pedido a 'EnProceso' (su estado actual)");
                 * pedidoCEN.CambiarEstado (id_pedido, EstadoEnum.enProceso);
                 * pedEN = new PedidoCAD ().ReadOIDDefault (id_pedido);
                 * Console.WriteLine ("El estado actual del pedido es: " + pedEN.Estado);
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a intentar cambiar el estado del pedido a 'Enviado'");
                 * pedidoCEN.CambiarEstado (id_pedido, EstadoEnum.enviado);
                 * pedEN = new PedidoCAD ().ReadOIDDefault (id_pedido);
                 * Console.WriteLine ("El estado actual del pedido es: " + pedEN.Estado);
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a intentar cambiar el estado del pedido2 a 'enProceso'");
                 * pedidoCEN.CambiarEstado (id_pedido2, EstadoEnum.enProceso);
                 * pedEN = new PedidoCAD ().ReadOIDDefault (id_pedido2);
                 * Console.WriteLine ("El estado actual del pedido es: " + pedEN.Estado);
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a intentar cambiar el estado del pedido3 a 'enProceso'");
                 * pedidoCEN.CambiarEstado (id_pedido3, EstadoEnum.enProceso);
                 * pedEN = new PedidoCAD ().ReadOIDDefault (id_pedido3);
                 * Console.WriteLine ("El estado actual del pedido es: " + pedEN.Estado);
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 *
                 *
                 * //CUSTOM TRANSACTION
                 *
                 * Console.WriteLine ("-------------COMPROBACIONES DE LOS CUSTOM TRANSACTION-------------");
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("-------------Cambio valoracion media producto-------------");
                 *
                 * Console.WriteLine ("La valoracion media del producto es: " + prodEN.Val_media);
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a añadir una nueva valoracion para ver si cambia la media");
                 * ValoracionEN valEN = valoracionCP.New_ (1, "No me gusta cambialo", id_producto, id_usu4);
                 * prodEN = new ProductoCAD ().ReadOIDDefault (id_producto);
                 * Console.WriteLine ("La valoracion media del producto es: " + prodEN.Val_media);
                 *
                 * Console.WriteLine ("Se va a borrar la nueva valoracion para ver si cambia correctamente la media del producto");
                 * valoracionCP.Destroy (valEN.Id);
                 * prodEN = new ProductoCAD ().ReadOIDDefault (id_producto);
                 * Console.WriteLine ("La valoracion media del producto es: " + prodEN.Val_media);
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 * Console.WriteLine ("-------------Confirmar la recepción de un pedido-------------");
                 *
                 * UsuarioEN usuarioEN = usuarioCEN.ReadOID (id_usu);
                 * pedEN = new PedidoCAD ().ReadOIDDefault (id_pedido);
                 * Console.WriteLine ("El pedido con la id " + id_pedido + " está ahora mismo en el estado: " + pedEN.Estado + ".");
                 *
                 * UsuarioCP usuarioCP = new UsuarioCP ();
                 * usuarioCP.ConfirmarRecepcion (id_usu, id_pedido);
                 *
                 * pedEN = new PedidoCAD ().ReadOID (id_pedido);
                 * Console.WriteLine ("Tras unos días el pedido le llega a casa y el usuario '" + usuarioEN.Nombre + "' confirma su llegada, siendo ahora el estado: " + pedEN.Estado + ".");
                 * Console.WriteLine ();
                 *
                 *
                 * Console.WriteLine ("-------------Devolver un pedido-------------");
                 *
                 * pedidoEN = new PedidoCAD ().ReadOIDDefault (id_pedido3);
                 *
                 * DevolucionEN dev = pedidoEN.Devolucion;
                 *
                 * Console.WriteLine ("El pedido actual tiene esta devolución: ");
                 * Console.WriteLine ("No tiene ahora mismo ninguna devolución. (El valor es nulo)");
                 * Console.WriteLine ("Ahora procedemos a devolver el pedido y comprobamos que exista la devolución: ");
                 *
                 * PedidoCP pedidoCP = new PedidoCP ();
                 * pedidoCP.DevolverPedido (id_pedido3, "No me gusta, cambiamelo", Motivo_DevolucionEnum.otros, id_usu);
                 * pedidoEN = new PedidoCAD ().ReadOIDDefault (id_pedido3);
                 * int idDev = pedidoEN.Devolucion.Id;
                 * dev = new DevolucionCAD ().ReadOIDDefault (idDev);
                 *
                 * Console.WriteLine ("El pedido actual tiene ahora esta devolución:");
                 *
                 * Console.WriteLine ("Devolución " + i + ": " + dev.Motivo + " y el estado del Pedido es '" + pedidoEN.Estado + "'.");
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 * //FUNCIONAMIENTO DEL NEW Y DESTROY DE LINEAPEDIDO AUTOCOMPLETANDO LA CANTIDAD Y PRECIO DEL PEDIDO
                 * Console.WriteLine ("-------------Crear Lineas de pedido afectando al Pedido-------------");
                 * Console.WriteLine ("Vamos a comprobar los datos actuales del pedido con la ID " + id_pedido2 + " (no tiene ninguna)");
                 *
                 * pedidoEN = new PedidoCAD ().ReadOIDDefault (id_pedido2);
                 * LineaPedidoCEN lineaPedidoCEN = new LineaPedidoCEN ();
                 * ProductoEN productoEN = productoCEN.ReadOID (id_producto3);
                 * ProductoEN productoEN2 = productoCEN.ReadOID (id_producto5);
                 *
                 *
                 * Console.WriteLine ("Precio total: " + pedidoEN.Total);
                 * Console.WriteLine ("Cantidad total de productos: " + pedidoEN.Cantidad);
                 *
                 * IList<LineaPedidoEN> lineas = lineaPedidoCEN.GetLineasPedido (id_pedido2);
                 *
                 * i = 0;
                 * foreach (LineaPedidoEN linea in lineas) {
                 *      i++;
                 *      Console.WriteLine ("Linea " + i + ": " + linea.Precio + "$ -- x" + linea.Cantidad);
                 * }
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ("Ahora creamos un par de lineas de pedido para actualizarlo");
                 *
                 * //int idLinea1 = lineaPedidoCP.New_ (2, id_pedido2, id_producto3).Id;
                 * //lineaPedidoCP.New_ (3, id_pedido2, id_producto);
                 *
                 * pedidoEN = new PedidoCAD ().ReadOIDDefault (id_pedido2);
                 *
                 * Console.WriteLine ("Precio total: " + pedidoEN.Total);
                 * Console.WriteLine ("Cantidad total de productos: " + pedidoEN.Cantidad);
                 *
                 * lineas = lineaPedidoCEN.GetLineasPedido (id_pedido2);
                 *
                 * i = 0;
                 * foreach (LineaPedidoEN linea in lineas) {
                 *      i++;
                 *      Console.WriteLine ("Linea " + i + ": " + linea.Precio + "$ -- x" + linea.Cantidad);
                 * }
                 *
                 * /*Console.WriteLine("Se va a intentar eliminar una de las lineas de pedido para que cambie el precio");
                 *
                 * lineaPedidoCP.Destroy(idLinea1);
                 *
                 * pedidoEN = new PedidoCAD().ReadOIDDefault(id_pedido2);
                 *
                 * Console.WriteLine("Precio total: " + pedidoEN.Total);
                 * Console.WriteLine("Cantidad total de productos: " + pedidoEN.Cantidad);
                 *
                 * lineas = lineaPedidoCEN.GetLineasPedido(id_pedido2);
                 *
                 * i = 0;
                 * foreach (LineaPedidoEN linea in lineas)
                 * {
                 *  i++;
                 *  Console.WriteLine("Linea " + i + ": " + linea.Precio + "$ -- x" + linea.Cantidad);
                 * }*/

                /*
                 * Console.WriteLine ("-------------Crear y borrar Entradas autocompletando la cantidad del Subforo-------------");
                 * SubforoEN subfEN = new SubforoCAD ().ReadOIDDefault (id_subforo);
                 * Console.WriteLine ("El subforo tiene " + subfEN.NumEntradas + "entradas");
                 *
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a intentar añadir una entrada al subforo para comprobar que se modifica el numero de entradas");
                 *
                 * EntradaEN entEN = entradaCP.New_ (id_subforo, id_usu2, "Que si que no me apetece pensar uevo.");
                 *
                 * subfEN = new SubforoCAD ().ReadOIDDefault (id_subforo);
                 * Console.WriteLine ("El subforo tiene " + subfEN.NumEntradas + " entradas");
                 *
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a intentar eliminar la nueva entrada de subforo para comprobar que se modifica el numero de entradas");
                 *
                 * entradaCP.Destroy (entEN.Id);
                 *
                 *
                 * subfEN = new SubforoCAD ().ReadOIDDefault (id_subforo);
                 * Console.WriteLine ("El subforo tiene " + subfEN.NumEntradas + "entradas");
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 *
                 *
                 *
                 * //READFILTERS
                 *
                 * Console.WriteLine ("-------------COMPROBACIONES DE LOS READFILTER-------------");
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("------------- Filtro de obtener las tarjetas de un usuario -------------");
                 *
                 * IList<TarjetaEN> tarjetas = tarjetaCEN.GetTarjetasUsuario (id_usu);
                 *
                 * i = 0;
                 * foreach (TarjetaEN tarj in tarjetas) {
                 *      i++;
                 *      Console.WriteLine ("Tarjeta " + i + ": " + tarj.Numero);
                 * }
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("------------- Filtro de obtener las direcciones de un usuario -------------");
                 *
                 * IList<DireccionEN> direcciones = direccionCEN.GetDireccionesUsuario (id_usu);
                 *
                 * i = 0;
                 * foreach (DireccionEN dir in direcciones) {
                 *      i++;
                 *      Console.WriteLine ("Direccion " + i + ": " + dir.Provincia + ", " + dir.Localidad + ", C/ " + dir.Calle);
                 * }
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener los pedidos que se encuentran en un estado específico -------------");
                 *
                 * IList<PedidoEN> pedidosEst = pedidoCEN.GetPedidosEstado (EstadoEnum.enProceso);
                 *
                 * i = 0;
                 * Console.WriteLine ("Los siguientes pedidos se encuentran en el estado 'En Proceso':");
                 * Console.WriteLine ();
                 * foreach (PedidoEN ped in pedidosEst) {
                 *      i++;
                 *      Console.WriteLine ("El pedido número " + i + ", con dirección: " + ped.Direccion);
                 * }
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("------------- Filtro de obtener los pedidos de un usuario específico -------------");
                 *
                 * IList<PedidoEN> pedidosUsu = pedidoCEN.GetPedidosUsuario (id_usu);
                 *
                 * i = 0;
                 * Console.WriteLine ("El usuario " + id_usu + " tiene los siguientes pedidos:");
                 * Console.WriteLine ();
                 * foreach (PedidoEN ped in pedidosUsu) {
                 *      i++;
                 *      Console.WriteLine ("El pedido número " + i + ", con dirección: " + ped.Direccion);
                 * }
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener las lineas de un pedido específico -------------");
                 *
                 * lineaPedidoCEN = new LineaPedidoCEN ();
                 * IList<LineaPedidoEN> lineasPedido = lineaPedidoCEN.GetLineasPedido (id_pedido);
                 *
                 * i = 0;
                 * Console.WriteLine ("Las lineas de este pedido tienen los siguientes precios: ");
                 * Console.WriteLine ();
                 * foreach (LineaPedidoEN linea in lineasPedido) {
                 *      i++;
                 *      Console.WriteLine ("La línea número " + i + ", con un precio de: " + linea.Precio + "$");
                 * }
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener los productos con un nombre -------------");
                 *
                 * IList<ProductoEN> productos = productoCEN.BuscarNombre ("Juego de Mesa");
                 *
                 * i = 0;
                 * Console.WriteLine ("Los productos de 'Juego de Mesa' son los siguientes: ");
                 * Console.WriteLine ();
                 * foreach (ProductoEN prod in productos) {
                 *      i++;
                 *      Console.WriteLine ("El producto número " + i + ", con un precio de " + prod.Precio + "$ se llama '" + prod.Nombre + "'");
                 * }
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener los productos de un tipo concreto -------------");
                 *
                 * productos = productoCEN.BuscarTipo (Tipo_productoEnum.dado);
                 *
                 * i = 0;
                 * Console.WriteLine ("Los productos de tipo 'Dado' son los siguientes: ");
                 * Console.WriteLine ();
                 * foreach (ProductoEN prod in productos) {
                 *      i++;
                 *      Console.WriteLine ("El producto número " + i + ", con un tipo de '" + prod.Tipo + "' se llama '" + prod.Nombre + "'");
                 * }
                 *
                 *
                 * Console.WriteLine ();
                 *
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener los productos dentro de un rango de precios -------------");
                 * IList<ProductoEN> listprodPrec = productoCEN.BuscarPrecio (1.99);
                 * Console.WriteLine ("productos con 1.99 de precio: ");
                 * i = 0;
                 * foreach (ProductoEN prod in listprodPrec) {
                 *      i++;
                 *      Console.WriteLine ("Producto con id: " + prod.Id);
                 * }
                 * if (i == 0)
                 *      Console.WriteLine ("No hay productos con ese precio");
                 * else
                 *      Console.WriteLine ("Hay " + i + " con ese precio");
                 * Console.WriteLine ();
                 *
                 * listprodPrec = productoCEN.BuscarPrecio (2.99);
                 * Console.WriteLine ("productos con 2.99 de precio: ");
                 * i = 0;
                 * foreach (ProductoEN prod in listprodPrec) {
                 *      i++;
                 *      Console.WriteLine ("Producto con id: " + prod.Id);
                 * }
                 * if (i == 0)
                 *      Console.WriteLine ("No hay productos con ese precio");
                 * else
                 *      Console.WriteLine ("Hay " + i + " con ese precio");
                 * Console.WriteLine ();
                 *
                 * listprodPrec = productoCEN.BuscarPrecio (20.99);
                 * Console.WriteLine ("productos con 20.99 de precio: ");
                 * i = 0;
                 * foreach (ProductoEN prod in listprodPrec) {
                 *      i++;
                 *      Console.WriteLine ("Producto con id: " + prod.Id);
                 * }
                 *
                 * if (i == 0)
                 *      Console.WriteLine ("No hay productos con ese precio");
                 * else
                 *      Console.WriteLine ("Hay " + i + " con ese precio");
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener los productos deseados de un usuario específico -------------");
                 * Console.WriteLine ();
                 *
                 * IList<ProductoEN> prodDes = productoCEN.GetProductosDeseadosUsuario (id_usu);
                 *
                 * i = 0;
                 * Console.WriteLine ("El usuario " + id_usu + " desea los siguientes productos:");
                 * Console.WriteLine ();
                 *
                 * foreach (ProductoEN prod in prodDes) {
                 *      i++;
                 *      Console.WriteLine ("El producto " + prod.Nombre + " es fervientemente deseado por nuestro usuario");
                 * }
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener los productos que tengan algun tipo de oferta -------------");
                 *
                 * IList<ProductoEN> listaoferta = productoCEN.BuscarOfertas ();
                 *
                 * i = 0;
                 * foreach (ProductoEN prod in listaoferta) {
                 *      i++;
                 *      Console.WriteLine ("El producto " + prod.Nombre + " esta en oferta");
                 * }
                 * if (i == 0)
                 *      Console.WriteLine ("No hay ningun producto en ofrta");
                 * else
                 *      Console.WriteLine ("Hay " + i + " productos en oferta");
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener los subforos creados por un usuario -------------");
                 * Console.WriteLine ("Los subforos que ha creado usu son: ");
                 * Console.WriteLine ();
                 * foreach (SubforoEN subf in subforoCEN.GetSubforosUsuario (id_usu)) {
                 *      Console.WriteLine ("Subforo con titulo: " + subf.Titulo);
                 * }
                 *
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener los subforos con un titulo -------------");
                 * IList<SubforoEN> subftit = subforoCEN.BuscarTitulo ("Mesa cuadrada para flexear de personaje 1");
                 *
                 * foreach (SubforoEN sub in subftit) {
                 *      Console.WriteLine ("El subforo con id " + sub.Id + " tiene de titulo 'Mesa cuadrada para flexear de personaje 1'");
                 * }
                 * Console.WriteLine ();
                 * subftit = subforoCEN.BuscarTitulo ("Mesa cuadrada para flexear de personaje 2");
                 *
                 * foreach (SubforoEN sub in subftit) {
                 *      Console.WriteLine ("El subforo con id " + sub.Id + " tiene de titulo 'Mesa cuadrada para flexear de personaje 2'");
                 * }
                 * Console.WriteLine ();
                 * subftit = subforoCEN.BuscarTitulo ("Mesa cuadrada para flexear de personaje 3");
                 *
                 * foreach (SubforoEN sub in subftit) {
                 *      Console.WriteLine ("El subforo con id " + sub.Id + " tiene de titulo 'Mesa cuadrada para flexear de personaje 3'");
                 * }
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 * Console.WriteLine ("------------- Filtro de obtener las valoraciones de un producto -------------");
                 * ValoracionCEN valoracionCEN = new ValoracionCEN ();
                 *
                 * ProductoCAD productoCAD = new ProductoCAD ();
                 * IList<ProductoEN> listaproductos = productoCAD.ReadAll (0, -1);
                 *
                 * int o;
                 * foreach (ProductoEN prod in listaproductos) {
                 *      IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ValoracionEN> listaValoraciones = valoracionCEN.GetValoracionesProducto (prod.Id);
                 *      o = 0;
                 *      foreach (ValoracionEN val in listaValoraciones) {
                 *              o++;
                 *              Console.WriteLine ("El producto con id: " + prod.Id + " tiene una valoracion de : " + val.Valor);
                 *      }
                 *      if (o == 0)
                 *              Console.WriteLine ("El producto con id: " + prod.Id + " no tiene ninguna valoracion");
                 *      else
                 *              Console.WriteLine ("Tiene un total de " + o + " valoraciones");
                 * }
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 *
                 * //RELATIONERS
                 *
                 * Console.WriteLine ("-------------COMPROBACIONES DE LOS RELATIONER-------------");
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 * Console.WriteLine ("-------------Metodo seguir subforo y de getSeguidosUsuario -------------");
                 *
                 * Console.WriteLine ("Los subforos que sigue usu son (no sigue ninguno): ");
                 * Console.WriteLine ();
                 * foreach (SubforoEN subf in subforoCEN.GetSeguidosUsuario (id_usu)) {
                 *      Console.WriteLine (subf.Titulo);
                 * }
                 * subforoCEN.SeguirSubforo (id_subforo, new List<int> { id_usu });
                 * subforoCEN.SeguirSubforo (id_subforo2, new List<int> { id_usu });
                 * subforoCEN.SeguirSubforo (id_subforo3, new List<int> { id_usu });
                 * subforoCEN.SeguirSubforo (id_subforo4, new List<int> { id_usu });
                 *
                 * Console.WriteLine ("Usu ha seguido los subforos: ");
                 * foreach (SubforoEN subf in subforoCEN.GetSeguidosUsuario (id_usu)) {
                 *      Console.WriteLine (subf.Titulo);
                 * }
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("-------------Metodo dejar de seguir subforo-------------");
                 *
                 * Console.WriteLine ("Los subforos que sigue son: ");
                 * foreach (SubforoEN subf in subforoCEN.GetSeguidosUsuario (id_usu)) {
                 *      Console.WriteLine (subf.Titulo);
                 * }
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a intentar hacer que usu deje de seguir a subforo");
                 * subforoCEN.DejarSeguirSubforo (id_subforo, new List<int> { id_usu });
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Los subforos que sigue son: ");
                 * foreach (SubforoEN subf in subforoCEN.GetSeguidosUsuario (id_usu)) {
                 *      Console.WriteLine (subf.Titulo);
                 * }
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("-------------Metodo marcar deseado-------------");
                 *
                 * Console.WriteLine ("Los productos deseados de usu2 (no tiene): ");
                 * Console.WriteLine ();
                 * foreach (ProductoEN fav in productoCEN.GetProductosDeseadosUsuario (id_usu2)) {
                 *      Console.WriteLine (fav.Nombre);
                 * }
                 *
                 * productoCEN.MarcarDeseado (id_producto, new List<int> { id_usu2 });
                 * productoCEN.MarcarDeseado (id_producto2, new List<int> { id_usu2 });
                 * productoCEN.MarcarDeseado (id_producto5, new List<int> { id_usu2 });
                 *
                 * Console.WriteLine ("Usu2 ha marcado como deseados: ");
                 * foreach (ProductoEN fav in productoCEN.GetProductosDeseadosUsuario (id_usu2)) {
                 *      Console.WriteLine (fav.Nombre);
                 * }
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("-------------Metodo quitar deseado-------------");
                 *
                 * Console.WriteLine ("Los productos deseados de usu2: ");
                 * Console.WriteLine ();
                 * foreach (ProductoEN fav in productoCEN.GetProductosDeseadosUsuario (id_usu2)) {
                 *      Console.WriteLine (fav.Nombre);
                 * }
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Se va a intentar hacer que usu2 quite a Dados de sus deseados");
                 * productoCEN.QuitarDeseado (id_producto, new List<int> { id_usu2 });
                 * Console.WriteLine ();
                 *
                 * Console.WriteLine ("Los productos deseados de usu2: ");
                 * Console.WriteLine ();
                 * foreach (ProductoEN fav in productoCEN.GetProductosDeseadosUsuario (id_usu2)) {
                 *      Console.WriteLine (fav.Nombre);
                 * }
                 * Console.WriteLine ();
                 * Console.WriteLine ();
                 *
                 *
                 * Console.WriteLine ("-------------Meter numero de telefono en usuario-------------");
                 *
                 * Console.WriteLine ("Se va a intentar ponerle numero de telefono a usuario");
                 * UsuarioEN usuario = new UsuarioCAD ().ReadOID (id_usu);
                 * string numero = "901234567";
                 * usuario.Telefono = numero;
                 * // Ver si cambiar esto o poner nueva funcion
                 * new UsuarioCAD ().ModifyDefault (usuario);
                 * usuario = new UsuarioCAD ().ReadOID (id_usu);
                 * Console.WriteLine ("El numero de telefono de usu1 es: " + usuario.Telefono);
                 *
                 *
                 */

                /*PROTECTED REGION END*/
        }
        catch (Exception ex)
        {
                System.Console.WriteLine (ex.InnerException);
                throw ex;
        }
}
}
}
