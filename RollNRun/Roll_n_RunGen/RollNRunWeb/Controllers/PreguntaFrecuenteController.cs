using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
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
    public class PreguntaFrecuenteController : BasicController
    {
        // GET: PreguntaFrecuente
        public ActionResult Index()
        {
            SessionInitialize();
            PreguntaFrecuenteCAD preguntaFrecuenteCAD = new PreguntaFrecuenteCAD(session);
            PreguntaFrecuenteCEN preguntaFrecuenteCEN = new PreguntaFrecuenteCEN(preguntaFrecuenteCAD);

            IList<PreguntaFrecuenteEN> preguntaFrecuentesEN = preguntaFrecuenteCEN.ReadAll(0, -1);
            IEnumerable<PreguntaFrecuenteViewModel> preguntaFrecuentesViewModel = new PreguntaFrecuenteAssembler().ConvertListENToModel(preguntaFrecuentesEN).ToList();
            SessionClose();

            return View(preguntaFrecuentesViewModel);
        }

        public ActionResult Indice()
        {
            SessionInitialize();
            PreguntaFrecuenteCAD preguntaFrecuenteCAD = new PreguntaFrecuenteCAD(session);
            PreguntaFrecuenteCEN preguntaFrecuenteCEN = new PreguntaFrecuenteCEN(preguntaFrecuenteCAD);

            IList<PreguntaFrecuenteEN> preguntaFrecuentesEN = preguntaFrecuenteCEN.ReadAll(0, -1);
            IEnumerable<PreguntaFrecuenteViewModel> preguntaFrecuentesViewModel = new PreguntaFrecuenteAssembler().ConvertListENToModel(preguntaFrecuentesEN).ToList();
            SessionClose();

            return View(preguntaFrecuentesViewModel);
        }

        // GET: PreguntaFrecuente/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();

            PreguntaFrecuenteCAD preguntaFrecuenteCAD = new PreguntaFrecuenteCAD(session);
            PreguntaFrecuenteCEN preguntaFrecuenteCEN = new PreguntaFrecuenteCEN(preguntaFrecuenteCAD);

            PreguntaFrecuenteEN preguntaFrecuenteEN = preguntaFrecuenteCEN.ReadOID(id);
            PreguntaFrecuenteViewModel preguntaFrecuenteViewModel = new PreguntaFrecuenteAssembler().ConvertENToModelUI(preguntaFrecuenteEN);

            SessionClose();

            return View(preguntaFrecuenteViewModel);
        }

        // GET: PreguntaFrecuente/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: PreguntaFrecuente/Create
        [HttpPost]
        public ActionResult Create(PreguntaFrecuenteViewModel faq)
        {
            try
            {
                PreguntaFrecuenteCEN preguntaFrecuenteCEN = new PreguntaFrecuenteCEN();
                preguntaFrecuenteCEN.New_(faq.pregunta, faq.respuesta);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: PreguntaFrecuente/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            PreguntaFrecuenteCAD preguntaFrecuenteCAD = new PreguntaFrecuenteCAD(session);
            PreguntaFrecuenteCEN preguntaFrecuenteCEN = new PreguntaFrecuenteCEN(preguntaFrecuenteCAD);

            PreguntaFrecuenteEN preguntaFrecuenteEN = preguntaFrecuenteCEN.ReadOID(id);
            PreguntaFrecuenteViewModel preguntaFrecuenteViewModel = new PreguntaFrecuenteAssembler().ConvertENToModelUI(preguntaFrecuenteEN);

            SessionClose();

            return View(preguntaFrecuenteViewModel);
        }

        // POST: PreguntaFrecuente/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, PreguntaFrecuenteViewModel faq)
        {
            try
            {
                PreguntaFrecuenteCEN preguntaFrecuenteCEN = new PreguntaFrecuenteCEN();
                PreguntaFrecuenteEN preguntaFrecuenteEN = preguntaFrecuenteCEN.ReadOID(id);
                preguntaFrecuenteCEN.Modify(id, faq.pregunta, faq.respuesta);


                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: PreguntaFrecuente/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            PreguntaFrecuenteCAD preguntaFrecuenteCAD = new PreguntaFrecuenteCAD(session);
            PreguntaFrecuenteCEN preguntaFrecuenteCEN = new PreguntaFrecuenteCEN(preguntaFrecuenteCAD);

            PreguntaFrecuenteEN preguntaFrecuenteEN = preguntaFrecuenteCEN.ReadOID(id);
            PreguntaFrecuenteViewModel preguntaFrecuenteViewModel = new PreguntaFrecuenteAssembler().ConvertENToModelUI(preguntaFrecuenteEN);

            SessionClose();

            return View(preguntaFrecuenteViewModel);
        }

        // POST: PreguntaFrecuente/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, PreguntaFrecuenteViewModel faq)
        {
            try
            {
                PreguntaFrecuenteCEN preguntaFrecuenteCEN = new PreguntaFrecuenteCEN();
                preguntaFrecuenteCEN.Destroy(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
