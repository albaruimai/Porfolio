using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using RollNRunWeb.Assemblers;
using RollNRunWeb.Models;
using System.IO;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;
using Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run;

namespace RollNRunWeb.Controllers
{
    public class ProductoController : BasicController
    {
        // GET: Producto
        public ActionResult Index()
        {
            SessionInitialize();
            ProductoCAD productoCAD = new ProductoCAD(session);
            ProductoCEN productoCEN = new ProductoCEN(productoCAD);

            IList<ProductoEN> productosEN = productoCEN.ReadAll(0, -1);
            IEnumerable<ProductoViewModel> productosViewModel = new ProductoAssembler().ConvertListENToModel(productosEN).ToList();
            SessionClose();

            return View(productosViewModel);
        }

        [Authorize]
        public ActionResult ListaDeseados()
        {
            try
            {
                SessionInitialize();
                ProductoCAD productoCAD = new ProductoCAD(session);
                ProductoCEN productoCEN = new ProductoCEN(productoCAD);

                IList<ProductoEN> productosEN = productoCEN.ReadAll(0, -1);

                IList<ProductoEN> productosDeseadosEN = productoCEN.GetProductosDeseadosUsuario(((UsuarioEN)Session["Usuario"]).Id);
                IEnumerable<ProductoViewModel> productosViewModel = new ProductoAssembler().ConvertListENToModel(productosDeseadosEN).ToList();
                SessionClose();

                return View(productosViewModel);
            }
            
            catch
            {
                return View();
            }
        }

        public ActionResult ValoracionesProducto(int id)
        {
            SessionInitialize();
            ValoracionCAD valoracionCAD = new ValoracionCAD(session);
            ValoracionCEN valoracionCEN = new ValoracionCEN(valoracionCAD);

            IList<ValoracionEN> valoracionesEN = valoracionCEN.GetValoracionesProducto(id);
            IEnumerable<ValoracionViewModel> valoracionesViewModel = new ValoracionAssembler().ConvertListENToModel(valoracionesEN).ToList();
            SessionClose();

            return PartialView(valoracionesViewModel);
        }
        [Authorize]
        public ActionResult Valorar()
        {
            return PartialView();
        }
        [HttpPost]
        public ActionResult Valorar(int id, ValoracionViewModel valoracion)
        {
            try
            {
                if (valoracion.valor < 1 || valoracion.valor > 5)
                {
                    return PartialView();
                }
                
                ValoracionCP valoracionCP = new ValoracionCP();
                if (Session["Usuario"] != null)
                {
                    valoracion.usuario = ((UsuarioEN)Session["Usuario"]).Id;
                    valoracion.producto = id;
                    valoracionCP.New_(valoracion.valor, valoracion.comentario, valoracion.producto, valoracion.usuario);
                }

                return PartialView();
            }
            catch
            {
                return PartialView();
            }
        }


        // GET: Producto/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();
            ProductoCAD productoCAD = new ProductoCAD(session);
            ProductoCEN productoCEN = new ProductoCEN(productoCAD);

            ProductoEN productoEN = productoCEN.ReadOID(id);
            ProductoViewModel productoViewModel = new ProductoAssembler().ConvertENToModelUI(productoEN);

            SessionClose();

            return View(productoViewModel);
        }
        [Authorize]
        // GET: Producto/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Producto/Create
        [HttpPost]
        public ActionResult Create(ProductoViewModel prod, HttpPostedFileBase file)
        {
            string fileName = "", path = "";
            // Verify that the user selected a file
            if (file != null && file.ContentLength > 0)
            {
                // extract only the fielname
                fileName = Path.GetFileName(file.FileName);
                // store the file inside ~/App_Data/uploads folder
                path = Path.Combine(Server.MapPath("~/Images/Uploads"), fileName);
                file.SaveAs(path);
                fileName = "/Images/Uploads/" + fileName;
            }

            else
            {
                fileName = "/Images/Sin_Imagen.png";
            }

            try
            {
                ProductoCEN productoCEN = new ProductoCEN();
                double nuevo_precio = Double.Parse(prod.precio.Replace(".", ","));
                productoCEN.New_(prod.nombre, prod.marca, prod.stock, nuevo_precio, fileName, prod.descripcion, 0, (Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Tipo_productoEnum)prod.tipo_producto, prod.oferta);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
        [Authorize]
        // GET: Producto/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            ProductoCAD productoCAD = new ProductoCAD(session);
            ProductoCEN productoCEN = new ProductoCEN(productoCAD);

            ProductoEN productoEN = productoCEN.ReadOID(id);
            ProductoViewModel productoViewModel = new ProductoAssembler().ConvertENToModelUI(productoEN);

            SessionClose();

            return View(productoViewModel);
        }

        // POST: Producto/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, ProductoViewModel prod, HttpPostedFileBase file)
        {
            string fileName = "", path = "";
            // Verify that the user selected a file
            if (file != null && file.ContentLength > 0)
            {
                // extract only the fielname
                fileName = Path.GetFileName(file.FileName);
                // store the file inside ~/App_Data/uploads folder
                path = Path.Combine(Server.MapPath("~/Images/Uploads"), fileName);
                file.SaveAs(path);
                fileName = "/Images/Uploads/" + fileName;
            }

            else
            {
                fileName = prod.imagen;
            }

            try
            {
                ProductoCEN productoCEN = new ProductoCEN();
                ProductoEN productoEN = productoCEN.ReadOID(id);
                double nuevo_precio = Double.Parse(prod.precio.Replace(".", ","));
                productoCEN.Modify(id, prod.nombre, prod.marca, prod.stock, nuevo_precio, fileName, prod.descripcion, productoEN.Val_media, prod.tipo_producto, prod.oferta);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
        [Authorize]
        // GET: Producto/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            ProductoCAD productoCAD = new ProductoCAD(session);
            ProductoCEN productoCEN = new ProductoCEN(productoCAD);

            ProductoEN productoEN = productoCEN.ReadOID(id);
            ProductoViewModel productoViewModel = new ProductoAssembler().ConvertENToModelUI(productoEN);

            SessionClose();

            return View(productoViewModel);
        }

        // POST: Producto/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, ProductoViewModel prod)
        {
            try
            {
                ProductoCEN productoCEN = new ProductoCEN();
                productoCEN.Destroy(id);


                IList<int> usuarioDeseado = new List<int>();
                usuarioDeseado.Add(((UsuarioEN)Session["Usuario"]).Id);

                IList<ProductoEN> productosEN = productoCEN.ReadAll(0, -1);
                productoCEN.MarcarDeseado(productosEN[0].Id, usuarioDeseado);
                productoCEN.MarcarDeseado(productosEN[1].Id, usuarioDeseado);
                productoCEN.MarcarDeseado(productosEN[2].Id, usuarioDeseado);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
        [Authorize]

        public ActionResult GuardarDeseado()
        {
            return PartialView();
        }
        [HttpPost]
        public ActionResult GuardarDeseado(int id)
        {
            try
            {
                ProductoCEN productoCEN = new ProductoCEN();
                IList<int> us = new List<int>();
                if (Session["Usuario"] != null)
                {
                    us.Add(((UsuarioEN)Session["Usuario"]).Id);
                    IList<ProductoEN> productosDeseados = productoCEN.GetProductosDeseadosUsuario(us[0]);
                    foreach (ProductoEN producto in productosDeseados)
                    {
                        if (producto.Id == id)
                        {
                            return PartialView();
                        }
                    }

                    productoCEN.MarcarDeseado(id, us);
                }

                return PartialView();
            }
            catch
            {
                return PartialView();
            }
        }

        [Authorize]
        public ActionResult QuitarDeseado()
        {
            return PartialView();
        }
        [HttpPost]
        public ActionResult QuitarDeseado(int id)
        {
            try
            {
                ProductoCEN productoCEN = new ProductoCEN();
                IList<int> us = new List<int>();
                if (Session["Usuario"] != null)
                {
                    us.Add(((UsuarioEN)Session["Usuario"]).Id);
                    IList<ProductoEN> productosDeseados = productoCEN.GetProductosDeseadosUsuario(us[0]);
                    bool existe = true;
                    foreach (ProductoEN producto in productosDeseados)
                    {
                        if (producto.Id == id)
                        {
                            existe = true;
                        }
                    }

                    if (existe)
                    {
                        productoCEN.QuitarDeseado(id, us);
                        return PartialView();
                    }
                }

                return PartialView();
            }
            catch
            {
                return PartialView();
            }
        }

        public ActionResult MeterCarrito()
        {
            return PartialView();
        }

        [HttpPost]
        public ActionResult MeterCarrito(int id)
        {
            try
            {
                // TODO: Add insert logic here
                SessionInitialize();
                PedidoCEN pedCEN = new PedidoCEN();
                LineaPedidoCP lin_pedCP = new LineaPedidoCP();
                IList<PedidoEN> pedidos = pedCEN.GetPedidosEstado(EstadoEnum.enCarrito);
                PedidoEN pedidoEN = new PedidoEN();
                PedidoCEN pedidoCEN = new PedidoCEN();
                if (pedidos.Count > 0)
                {
                    pedidoEN = pedidos[0];
                }
                else
                {
                    int id_ped = pedidoCEN.New_(DateTime.Now, ((UsuarioEN)Session["Usuario"]).Id);
                    pedidoCEN.CambiarEstado(id_ped, EstadoEnum.enCarrito);

                    pedidoEN = pedCEN.ReadOID(id_ped);
                }

                if (Session["Usuario"] != null)
                {
                    lin_pedCP.New_(1, pedidoEN.Id, id);
                }

                SessionClose();

                return PartialView();

            }
            catch
            {
                return PartialView();
            }
        }
    }
}
