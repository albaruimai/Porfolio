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

namespace RollNRunWeb.Controllers
{
    [Authorize]
    public class DireccionController : BasicController
    {
        // GET: Direccion
        public ActionResult Index()
        {
            SessionInitialize();

            DireccionCAD dirCad = new DireccionCAD(session);
            DireccionCEN dirCEN = new DireccionCEN(dirCad);

            IList<DireccionEN> listEN = dirCEN.GetDireccionesUsuario(((UsuarioEN)Session["Usuario"]).Id);
            IEnumerable<DireccionViewModel> listViewModel = new DireccionAssembler().ConvertListENToModel(listEN).ToList();

            SessionClose();

            return View(listViewModel);
        }

        // GET: Direccion/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();
            DireccionCAD dirCAD = new DireccionCAD(session);
            DireccionCEN dirCEN = new DireccionCEN(dirCAD);

            DireccionEN dirEN = dirCEN.ReadOID(id);
            DireccionViewModel direccionViewModel = new DireccionAssembler().ConvertENToModelUI(dirEN);
            SessionClose();

            return View(direccionViewModel);
        }

        // GET: Direccion/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Direccion/Create
        [HttpPost]
        public ActionResult Create(DireccionViewModel dir)
        {
            try
            {
                // TODO: Add insert logic here
                DireccionCEN dirCEN = new DireccionCEN();
                if (Session["Usuario"] != null)
                {
                    dir.usuario = ((UsuarioEN)Session["Usuario"]).Id;
                }
                dirCEN.New_(dir.Provincia, dir.Localidad, dir.CP, dir.Calle, dir.usuario); //el 0 debería ser la ID de un Usuario, como aun no
                // hemos hecho Usuario lo he dejado como "0" para no crear un Usuario por si acaso


                return RedirectToAction("Index"); //No redirige, no se por qué, mi teoría es por no poner bien el Usuario
                //pero no estoy seguro
            }
            catch
            {
                return View();
            }
        }

        // GET: Direccion/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            DireccionCAD dirCAD = new DireccionCAD(session);
            DireccionCEN dirCEN = new DireccionCEN(dirCAD);

            DireccionEN dirEN = dirCEN.ReadOID(id);
            DireccionViewModel direccionViewModel = new DireccionAssembler().ConvertENToModelUI(dirEN);

            SessionClose();

            return View(direccionViewModel);
        }

        // POST: Direccion/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, DireccionViewModel dir)
        { 
            try
            {
                DireccionCEN dirCEN = new DireccionCEN();
                DireccionEN dirEN = dirCEN.ReadOID(id);
                dirCEN.Modify(id, dir.Provincia, dir.Localidad, dir.CP, dir.Calle);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Direccion/Delete/5
        public ActionResult Delete(int id)
        {
            return View();
        }

        // POST: Direccion/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, FormCollection collection)
        {
            try
            {
                DireccionCEN dirCEN = new DireccionCEN();
                dirCEN.Destroy(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
