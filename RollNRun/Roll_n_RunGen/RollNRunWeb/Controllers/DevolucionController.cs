using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;
using RollNRunWeb.Models;
using RollNRunWeb.Assemblers;

namespace RollNRunWeb.Controllers
{
    public class DevolucionController : BasicController
    {
        // GET: Devolucion
        public ActionResult Index()
        {
            SessionInitialize();
            DevolucionCAD devolucionCAD = new DevolucionCAD(session);
            DevolucionCEN devolucionCEN = new DevolucionCEN(devolucionCAD);

            IList<DevolucionEN> devolucionesEN = devolucionCEN.ReadAll(0, -1);
            IEnumerable<DevolucionViewModel> devolucionViewModel = new DevolucionAssembler().ConvertListENToModel(devolucionesEN).ToList();
            SessionClose();

            return View(devolucionViewModel);
        }
        [Authorize]
        // GET: Devolucion/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();
            DevolucionCAD devolucionCAD = new DevolucionCAD(session);
            DevolucionCEN devolucionCEN = new DevolucionCEN(devolucionCAD);

            DevolucionEN devolucionEN = devolucionCEN.ReadOID(id);
            DevolucionViewModel devolucionViewModel = new DevolucionAssembler().ConvertENToModelUI(devolucionEN);
            SessionClose();

            return View(devolucionViewModel);
        }
        [Authorize]
        // GET: Devolucion/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Devolucion/Create
        [HttpPost]
        public ActionResult Create(DevolucionViewModel dev)
        {
            try
            {
                // TODO: Add insert logic here
                DevolucionCEN devolucionCEN = new DevolucionCEN();
                if (Session["Usuario"] != null)
                {
                    dev.usuario = ((UsuarioEN)Session["Usuario"]).Id;
                    //dev.pedido = id; se ha cambiado esto a vista parcial en pedido donde en el actionResult se le pase la id del pedido
                    devolucionCEN.New_(dev.Descripcion, dev.Motivo, dev.pedido, dev.usuario);
                }

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
        [Authorize]
        // GET: Devolucion/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            DevolucionCAD devolucionCAD = new DevolucionCAD(session);
            DevolucionCEN devolucionCEN = new DevolucionCEN(devolucionCAD);

            DevolucionEN devolucionEN = devolucionCEN.ReadOID(id);
            DevolucionViewModel devolucionViewModel = new DevolucionAssembler().ConvertENToModelUI(devolucionEN);

            SessionClose();

            return View(devolucionViewModel);
        }

        // POST: Devolucion/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, DevolucionViewModel dev)
        {
            try
            {
                // TODO: Add update logic here

                DevolucionCEN devolucionCEN = new DevolucionCEN();
                DevolucionEN devolucionEN = devolucionCEN.ReadOID(id);
                devolucionCEN.Modify(id, dev.Descripcion, dev.Motivo);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
        [Authorize]
        // GET: Devolucion/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            DevolucionCAD devolucionCAD = new DevolucionCAD(session);
            DevolucionCEN devolucionCEN = new DevolucionCEN(devolucionCAD);

            DevolucionEN devolucionEN = devolucionCEN.ReadOID(id);
            DevolucionViewModel devolucionViewModel = new DevolucionAssembler().ConvertENToModelUI(devolucionEN);
            SessionClose();

            return View(devolucionViewModel);
        }

        // POST: Devolucion/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, DevolucionViewModel dev)
        {
            try
            {
                // TODO: Add delete logic here

                DevolucionCEN devolucionCEN = new DevolucionCEN();
                devolucionCEN.Destroy(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
