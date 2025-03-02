using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Assemblers;
using RollNRunWeb.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace RollNRunWeb.Controllers
{
    [Authorize]
    public class FacturaController : BasicController
    {
        // GET: Factura
        public ActionResult Index()
        {
            SessionInitialize();
            FacturaCAD facturaCAD = new FacturaCAD(session);
            FacturaCEN facturaCEN = new FacturaCEN(facturaCAD);

            IList<FacturaEN> facturasEN = facturaCEN.ReadAll(0, -1);
            IEnumerable<FacturaViewModel> facturasViewModel = new FacturaAssembler().ConvertListENToModel(facturasEN).ToList();
            SessionClose();

            return View(facturasViewModel);
        }

        // GET: Factura/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();

            FacturaCAD facturaCAD = new FacturaCAD(session);
            FacturaCEN facturaCEN = new FacturaCEN(facturaCAD);

            FacturaEN facturaEN = facturaCEN.ReadOID(id);
            FacturaViewModel facturaViewModel = new FacturaAssembler().ConvertENToModelUI(facturaEN);

            SessionClose();

            return View(facturaViewModel);
        }

        // GET: Factura/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Factura/Create
        [HttpPost]
        public ActionResult Create(FacturaViewModel fact)
        {
            try
            {
                FacturaCP facturaCP = new FacturaCP();
                PedidoCEN pedidoCEN = new PedidoCEN();

                facturaCP.New_(DateTime.Now, fact.pedido);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Factura/Edit/5
        public ActionResult Edit(int id)
        {
            return View();
        }

        // POST: Factura/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, FacturaViewModel fact)
        {
            try
            {

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Factura/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            FacturaCAD facturaCAD = new FacturaCAD(session);
            FacturaCEN facturaCEN = new FacturaCEN(facturaCAD);

            FacturaEN facturaEN = facturaCEN.ReadOID(id);
            FacturaViewModel facturaViewModel = new FacturaAssembler().ConvertENToModelUI(facturaEN);

            SessionClose();

            return View(facturaViewModel);
        }

        // POST: Factura/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, FacturaViewModel fact)
        {
            try
            {
                FacturaCEN facturaCEN = new FacturaCEN();
                facturaCEN.Destroy(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
