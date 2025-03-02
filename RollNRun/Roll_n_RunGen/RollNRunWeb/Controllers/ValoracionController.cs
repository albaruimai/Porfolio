using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Assemblers;
using RollNRunWeb.Models;

namespace RollNRunWeb.Controllers
{
    public class ValoracionController : BasicController
    {

        [Authorize]
        // GET: Valoracion
        public ActionResult Index()
        {
            SessionInitialize();
            ValoracionCAD valCAD = new ValoracionCAD(session);
            ValoracionCEN valCEN = new ValoracionCEN(valCAD);
            IList<ValoracionEN> listEN = valCEN.GetValoracionesUsuario(((UsuarioEN)Session["Usuario"]).Id);
            IEnumerable<ValoracionViewModel> listViewModel = new ValoracionAssembler().ConvertListENToModel(listEN).ToList();
            SessionClose();

            return View(listViewModel);
        }

        // GET: Valoracion/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();
            ValoracionCAD valCAD = new ValoracionCAD(session);
            ValoracionCEN valCEN = new ValoracionCEN(valCAD);

            ValoracionEN valEN = valCEN.ReadOID(id);
            ValoracionViewModel valViewModel = new ValoracionAssembler().ConvertENToModelUI(valEN);

            SessionClose();

            return View(valViewModel);
        }

        // GET: Valoracion/Create
        public ActionResult Create()
        {
            IList<ProductoEN> listaProductos = new ProductoCEN().ReadAll(0, -1);
            IList<SelectListItem> productosItems = new List<SelectListItem>();

            foreach (ProductoEN prod in listaProductos)
            {
                productosItems.Add(new SelectListItem { Text = prod.Nombre, Value = prod.Id.ToString() });
            }

            ViewData["producto"] = productosItems;
            return View();
        }

        // POST: Valoracion/Create
        [HttpPost]
        public ActionResult Create(ValoracionViewModel val)
        {
            try
            {
                if (Session["Usuario"] != null)
                {
                    val.usuario = ((UsuarioEN)Session["Usuario"]).Id;
                }
                ValoracionCP valCP = new ValoracionCP();
                valCP.New_(val.valor, val.comentario, val.producto, val.usuario);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Valoracion/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            ValoracionCAD valCAD = new ValoracionCAD(session);
            ValoracionCEN valCEN = new ValoracionCEN(valCAD);

            ValoracionEN valEN = valCEN.ReadOID(id);
            ValoracionViewModel valViewModel = new ValoracionAssembler().ConvertENToModelUI(valEN);

            SessionClose();

            return View(valViewModel);
        }

        // POST: Valoracion/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, ValoracionViewModel val)
        {
            try
            {
                SessionInitialize();
                ValoracionCAD valCAD = new ValoracionCAD(session);
                ValoracionCEN valCEN = new ValoracionCEN(valCAD);

                ValoracionEN valEN = valCEN.ReadOID(id);
                ValoracionCP valCP = new ValoracionCP();
                valCP.Modify(val.id, val.valor, val.comentario, valEN.Producto.Id);

                SessionClose();

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Valoracion/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            ValoracionCAD valCAD = new ValoracionCAD(session);
            ValoracionCEN valCEN = new ValoracionCEN(valCAD);

            ValoracionEN valEN = valCEN.ReadOID(id);
            ValoracionViewModel valViewModel = new ValoracionAssembler().ConvertENToModelUI(valEN);

            SessionClose();

            return View(valViewModel);
        }

        // POST: Valoracion/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, ValoracionViewModel val)
        {
            try
            {
                ValoracionCP valCP = new ValoracionCP();
                valCP.Destroy(val.id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
