using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using RollNRunWeb.Models;
using RollNRunWeb.Assemblers;
using System.IO;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;
using Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run;

namespace RollNRunWeb.Controllers
{
    [Authorize]
    public class PedidoController : BasicController
    {
        // GET: Pedido
        public ActionResult Index()
        {
            SessionInitialize();

            PedidoCAD pedCad = new PedidoCAD(session);
            PedidoCEN pedCEN = new PedidoCEN(pedCad);

            IList<PedidoEN> listEN = pedCEN.ReadAll(0, -1);
            IEnumerable<PedidoViewModel> listViewModel = new PedidoAssembler().ConvertListENToModel(listEN).ToList();

            SessionClose();

            return View(listViewModel);
        }

        // GET: Pedido/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();
            PedidoCAD pedCAD = new PedidoCAD(session);
            PedidoCEN pedCEN = new PedidoCEN(pedCAD);

            PedidoEN pedEN = pedCEN.ReadOID(id);
            PedidoViewModel pedidoViewModel = new PedidoAssembler().ConvertENToModelUI(pedEN);
            SessionClose();

            return View(pedidoViewModel);
        }

        // GET: Pedido/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Pedido/Create
        [HttpPost]
        public ActionResult Create(PedidoViewModel ped)
        //Al crear, pues no crea el total y la cantidad, entiendo el porqué, ya que abajo no lo pongo, pero como no
        //me dejaba ponerlo, prefiero preguntar primero antes de tocar algo y liarla
        {
            try
            {
                // TODO: Add insert logic here
                PedidoCEN pedCEN = new PedidoCEN();
                if (Session["Usuario"] != null)
                {
                    ped.usuario = ((UsuarioEN)Session["Usuario"]).Id;
                    pedCEN.New_(DateTime.Now, ((UsuarioEN)Session["Usuario"]).Id);
                }
                // pedCEN.New_(ped.Fecha, ped.Dirección, ped.usuario);
                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Pedido/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            PedidoCAD pedidoCAD = new PedidoCAD(session);
            PedidoCEN pedidoCEN = new PedidoCEN(pedidoCAD);

            PedidoEN pedidoEN = pedidoCEN.ReadOID(id);
            PedidoViewModel pedidoViewModel = new PedidoAssembler().ConvertENToModelUI(pedidoEN);

            SessionClose();

            return View(pedidoViewModel);
        }

        // POST: Pedido/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, PedidoViewModel ped)
        //Hay un problema al editar el Total, solo permite editar números enteros, si pones una "," no te deja y si pones un "."
        //lo asume como 0
        {
            try
            {
                PedidoCEN pedidoCEN = new PedidoCEN();
                PedidoEN pedidoEN = pedidoCEN.ReadOID(id);
                pedidoCEN.Modify(id, DateTime.Now,  pedidoEN.Total, pedidoEN.Cantidad, ped.MetodoPago, pedidoEN.Estado);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Pedido/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            PedidoCAD pedCAD = new PedidoCAD(session);
            PedidoCEN pedCEN = new PedidoCEN(pedCAD);

            PedidoEN pedEN = pedCEN.ReadOID(id);
            PedidoViewModel pedViewModel = new PedidoAssembler().ConvertENToModelUI(pedEN);

            SessionClose();

            return View(pedViewModel);
        }

        // POST: Pedido/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, PedidoViewModel ped)
        {
            try
            {
                PedidoCEN pedCEN = new PedidoCEN();
                LineaPedidoCEN lpedCEN = new LineaPedidoCEN();
                LineaPedidoCP lpedCP = new LineaPedidoCP();
                IList<LineaPedidoEN> lineas = lpedCEN.GetLineasPedido(id);

                foreach (LineaPedidoEN pe in lineas)
                {
                    lpedCP.Destroy(pe.Id);
                }

                pedCEN.Destroy(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        public ActionResult Devolver()
        {
            return View();
        }
        [HttpPost]
        public ActionResult Devolver(int id, DevolucionViewModel dev)
        {
            try
            {
                // TODO: Add insert logic here
                DevolucionCEN devolucionCEN = new DevolucionCEN();
                PedidoCP pedidoCP = new PedidoCP();
                if (Session["Usuario"] != null)
                {
                    dev.usuario = ((UsuarioEN)Session["Usuario"]).Id;
                    pedidoCP.DevolverPedido(id, dev.Descripcion, dev.Motivo, dev.usuario);
                }

                return View();
            }
            catch
            {
                return View();
            }
        }

        public ActionResult Carrito()
        {
            try
            {
                SessionInitialize();

                PedidoCAD pedCad = new PedidoCAD(session);
                PedidoCEN pedCEN = new PedidoCEN(pedCad);

                IList<PedidoEN> listEN = pedCEN.ReadAll(0, -1);
                PedidoViewModel pedVM = new PedidoViewModel();

                foreach (PedidoEN pedEN in listEN)
                {
                    if (pedEN.Estado == Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.EstadoEnum.enCarrito)
                    {
                        pedVM = new PedidoAssembler().ConvertENToModelUI(pedEN);
                        
                    }

                }
                SessionClose();

                return View(pedVM);
            }
            catch
            {
                return View();
            }
        }

        public ActionResult LineasCarrito(int id)
        {

            SessionInitialize();
            LineaPedidoCAD linpedCAD = new LineaPedidoCAD(session);
            LineaPedidoCEN linpedCEN = new LineaPedidoCEN(linpedCAD);

            IList<LineaPedidoEN> linpedEN = linpedCEN.GetLineasPedido(id);
            IList<LineaPedidoViewModel> lineapedidoViewModel = new LineaPedidoAssembler().ConvertListENToModel(linpedEN);
            SessionClose();


            return PartialView(lineapedidoViewModel);
        }

        public ActionResult Tramite()
        {
            try
            {
                SessionInitialize();

                PedidoCAD pedCad = new PedidoCAD(session);
                PedidoCEN pedCEN = new PedidoCEN(pedCad);

                IList<PedidoEN> listEN = pedCEN.ReadAll(0, -1);
                PedidoViewModel pedVM = new PedidoViewModel();

                foreach (PedidoEN pedEN in listEN)
                {
                    if (pedEN.Estado == Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.EstadoEnum.enCarrito)
                    {
                        pedVM = new PedidoAssembler().ConvertENToModelUI(pedEN);

                    }
                }
                //Añadiendo las tarjetas al selector
                TarjetaCAD tarCAD = new TarjetaCAD(session);
                TarjetaCEN tarCEN = new TarjetaCEN(tarCAD);
                IList<TarjetaEN> tarjs = new TarjetaCEN().GetTarjetasUsuario(((UsuarioEN)Session["Usuario"]).Id);
                IList<SelectListItem> tarjIt = new List<SelectListItem>();
                foreach (TarjetaEN tar in tarjs)
                {
                    tarjIt.Add(new SelectListItem { Text = tar.Numero, Value = tar.Id.ToString() });
                }
                
                ViewData["tarjetaId"] = tarjIt;


                //Añadiendo las direcciones al selector

                IList<DireccionEN> dirs = new DireccionCEN().GetDireccionesUsuario(((UsuarioEN)Session["Usuario"]).Id);
                IList<SelectListItem> dirIt = new List<SelectListItem>();

                foreach (DireccionEN dir in dirs)
                {
                    dirIt.Add(new SelectListItem { Text = dir.Calle, Value = dir.Id.ToString() });
                }
                tarjIt.Add(new SelectListItem { Text = "Paypal", Value = 2.ToString() });
                ViewData["direccionId"] = dirIt;
                SessionClose();

                return View(pedVM);
            }
            catch
            {
                return View();
            }
        }


        [HttpPost]
        public ActionResult Tramite(int id, PedidoViewModel ped)
        {

            try
            {
                if (ped.direccion != 0 && ped.tarjeta != 0 ) {

                    PedidoCEN pedidoCEN = new PedidoCEN();
                    pedidoCEN.CambiarEstado(id, EstadoEnum.enProceso);
                    return RedirectToAction("Paga");
                }
                else{
                    return RedirectToAction("Error");
                }
                
            }
            catch
            {
                return View();
            }

        }


        public ActionResult SelectorTarjeta(int id)
        {

            SessionInitialize();
            TarjetaCAD tarCAD = new TarjetaCAD(session);
            TarjetaCEN tarCEN = new TarjetaCEN(tarCAD);

            IList<TarjetaEN> tarEN = tarCEN.GetTarjetasUsuario(((UsuarioEN)Session["Usuario"]).Id);
            IList<TarjetaViewModel> tarViewModel = new TarjetaAssembler().ConvertListENToModel(tarEN);
            SessionClose();

            IList<DireccionEN> dirs = new DireccionCEN().GetDireccionesUsuario(((UsuarioEN)Session["Usuario"]).Id);
            IList<SelectListItem> dirIt = new List<SelectListItem>();

            foreach (DireccionEN dir in dirs)
            {
                dirIt.Add(new SelectListItem { Text = dir.Calle, Value = dir.Id.ToString() });
            }
            ViewData["direccionId"] = dirIt;

            IList<TarjetaEN> tarjs = new TarjetaCEN().GetTarjetasUsuario(((UsuarioEN)Session["Usuario"]).Id);
            IList<SelectListItem> tarjIt = new List<SelectListItem>();

            foreach (TarjetaEN tar in tarjs)
            {
                tarjIt.Add(new SelectListItem { Text = tar.Numero, Value = tar.Id.ToString() });
            }
            tarjIt.Add(new SelectListItem {Text = "Paypal", Value = 2.ToString()});
            ViewData["tarjetaId"] = tarjIt;

            return PartialView();
        }
            public ActionResult Paga()
        {
            /*
            try
            {
                SessionInitialize();
                
                PedidoCAD pedCad = new PedidoCAD(session);
                PedidoCEN pedCEN = new PedidoCEN(pedCad);

                PedidoEN pedEN = pedCEN.ReadOID(id);
                PedidoViewModel pedVM = new PedidoViewModel();



                SessionClose();
                return View();
            }
            catch
            {
                return View();
            }
                */
            return View();
        }

        public ActionResult Error()
        {
            return View();
        }






        }
}
