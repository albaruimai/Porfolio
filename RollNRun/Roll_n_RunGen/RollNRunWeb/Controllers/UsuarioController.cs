using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using RollNRunWeb.Assemblers;
using RollNRunWeb.Models;
using System.IO;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;

namespace RollNRunWeb.Controllers
{
    [Authorize]
    public class UsuarioController : BasicController
    {
        // GET: Usuario
        public ActionResult Index()
        {
            SessionInitialize();
            UsuarioCAD usuarioCAD = new UsuarioCAD(session);
            UsuarioCEN usuarioCEN = new UsuarioCEN(usuarioCAD);

            IList<UsuarioEN> usuariosEN = usuarioCEN.ReadAll(0, -1);
            IEnumerable<UsuarioViewModel> usuariosViewModel = new UsuarioAssembler().ConvertListENToModel(usuariosEN).ToList();
            SessionClose();

            return View(usuariosViewModel);
        }

        // GET: Usuario/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();

            UsuarioCAD usuarioCAD = new UsuarioCAD(session);
            UsuarioCEN usuarioCEN = new UsuarioCEN(usuarioCAD);

            UsuarioEN usuarioEN = usuarioCEN.ReadOID(id);
            UsuarioViewModel usuarioViewModel = new UsuarioAssembler().ConvertENToModelUI(usuarioEN);

            SessionClose();

            return View(usuarioViewModel);
        }

        // GET: Usuario/Details/5
        public ActionResult Perfil()
        {
            SessionInitialize();

            UsuarioCAD usuarioCAD = new UsuarioCAD(session);
            UsuarioCEN usuarioCEN = new UsuarioCEN(usuarioCAD);

            UsuarioEN usuarioEN = usuarioCEN.ReadOID( (int) Session["Usu_id"]);
            UsuarioViewModel usuarioViewModel = new UsuarioAssembler().ConvertENToModelUI(usuarioEN);

            SessionClose();

            return View(usuarioViewModel);
        }

        // GET: Usuario/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Usuario/Create
        [HttpPost]
        public ActionResult Create(UsuarioViewModel usu, HttpPostedFileBase file)
        {
            string fileName = "", path = "";
            // Verify that the user selected a file
            if (file != null && file.ContentLength > 0)
            {
                // extract only the fielname
                fileName = Path.GetFileName(file.FileName);
                // store the file inside ~/App_Data/uploads folder
                path = Path.Combine(Server.MapPath("~/Images/ProfilePics"), fileName);
                file.SaveAs(path);
                fileName = "/Images/ProfilePics/" + fileName;
            }

            else
            {
                fileName = "/Images/Sin_Imagen.png";
            }

            try
            {
                UsuarioCEN usuarioCEN = new UsuarioCEN();
                int idUsu = usuarioCEN.New_(usu.nombre, usu.Email, usu.apellidos, usu.alias, usu.Password, usu.rol, fileName);
                UsuarioEN usuarioEN = usuarioCEN.ReadOID(idUsu);

                if (usu.telefono != null)           //Si no es un campo vacio se le añade ese nuevo telefono
                {
                    usuarioEN.Telefono = usu.telefono;
                }

                else
                {
                    usuarioEN.Telefono = "Sin registrar";
                }

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Usuario/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            UsuarioCAD usuarioCAD = new UsuarioCAD(session);
            UsuarioCEN usuarioCEN = new UsuarioCEN(usuarioCAD);

            UsuarioEN usuarioEN = usuarioCEN.ReadOID(id);
            UsuarioViewModel usuarioViewModel = new UsuarioAssembler().ConvertENToModelUI(usuarioEN);

            SessionClose();

            return View(usuarioViewModel);
        }

        // POST: Usuario/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, UsuarioViewModel usu, HttpPostedFileBase file)
        {
            string fileName = "", path = "";
            // Verify that the user selected a file
            if (file != null && file.ContentLength > 0)
            {
                // extract only the fielname
                fileName = Path.GetFileName(file.FileName);
                // store the file inside ~/App_Data/uploads folder
                path = Path.Combine(Server.MapPath("~/Images/ProfilePics"), fileName);
                file.SaveAs(path);
                fileName = "/Images/ProfilePics/" + fileName;
            }

            else
            {
                fileName = usu.imagen_perfil;
            }

            try
            {
                UsuarioCEN usuarioCEN = new UsuarioCEN();
                usuarioCEN.Modify(id, usu.nombre, usu.Email, usu.apellidos, usu.alias, usu.Password, usu.rol, usu.imagen_perfil);

                if (usu.telefono != null)     //Si no es un campo vacio se le añade ese nuevo telefono
                {
                    UsuarioEN usuarioEN = usuarioCEN.ReadOID(id);
                    usuarioEN.Telefono = usu.telefono;
                }

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Usuario/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            UsuarioCAD usuarioCAD = new UsuarioCAD(session);
            UsuarioCEN usuarioCEN = new UsuarioCEN(usuarioCAD);

            UsuarioEN usuarioEN = usuarioCEN.ReadOID(id);
            UsuarioViewModel usuarioViewModel = new UsuarioAssembler().ConvertENToModelUI(usuarioEN);

            SessionClose();

            return View(usuarioViewModel);
        }

        // POST: Usuario/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, FormCollection collection)
        {
            try
            {
                UsuarioCEN usuarioCEN = new UsuarioCEN();
                UsuarioEN usuarioEN = usuarioCEN.ReadOID(id);

                ProductoCEN productoCEN = new ProductoCEN();
                IList<ProductoEN> productos = productoCEN.GetProductosDeseadosUsuario(id);
                IList<int> idUsuario = new List<int>();
                idUsuario.Add(id);
                foreach (ProductoEN producto in productos)
                {
                    productoCEN.QuitarDeseado(producto.Id, idUsuario);
                }

                //UNRELATIONER DE SUBFOROS
                SubforoCEN subforoCEN = new SubforoCEN();
                IList<SubforoEN> subforos = subforoCEN.GetSeguidosUsuario(id);
                foreach (SubforoEN subforo in subforos)
                {
                    subforoCEN.DejarSeguirSubforo(subforo.Id, idUsuario);
                }

                TarjetaCEN tarjetaCEN = new TarjetaCEN();
                IList<TarjetaEN> tarjetas = tarjetaCEN.GetTarjetasUsuario(id);
                foreach (TarjetaEN tarjeta in tarjetas)
                {
                    tarjetaCEN.Destroy(tarjeta.Id);
                }

                DireccionCEN direccionCEN = new DireccionCEN();
                IList<DireccionEN> direcciones = direccionCEN.GetDireccionesUsuario(id);
                foreach (DireccionEN direccion in direcciones)
                {
                    direccionCEN.Destroy(direccion.Id);
                }

                PedidoCEN pedidoCEN = new PedidoCEN();
                IList<PedidoEN> pedidos = pedidoCEN.GetPedidosUsuario(id);
                foreach (PedidoEN pedido in pedidos)
                {
                    pedidoCEN.Destroy(pedido.Id);
                }
                
                ValoracionCEN valoracionCEN = new ValoracionCEN();
                ValoracionCP valoracionCP = new ValoracionCP();
                IList<ValoracionEN> valoraciones = valoracionCEN.GetValoracionesUsuario(id);
                foreach (ValoracionEN valoracion in valoraciones)
                {
                    valoracionCP.Destroy(valoracion.Id);
                }

                EntradaCEN entradaCEN = new EntradaCEN();
                EntradaCP entradaCP = new EntradaCP();
                IList<EntradaEN> entradas = entradaCEN.GetEntradasUsuario(id);
                foreach (EntradaEN entrada in entradas)
                {
                    entradaCP.Destroy(entrada.Id);
                }

                subforos = subforoCEN.GetSubforosUsuario(id);
                foreach (SubforoEN subforo in subforos)
                {
                    subforoCEN.Destroy(subforo.Id);
                }

                usuarioCEN.Destroy(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
