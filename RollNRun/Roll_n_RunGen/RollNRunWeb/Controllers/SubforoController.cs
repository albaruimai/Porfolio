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
    public class SubforoController : BasicController
    {
        // GET: Subforo
        public ActionResult Index()
        {
            SessionInitialize();
            SubforoCAD subforoCAD = new SubforoCAD(session);
            SubforoCEN subforoCEN = new SubforoCEN(subforoCAD);

            IList<SubforoEN> subforosEN = subforoCEN.ReadAll(0, -1);
            IEnumerable<SubforoViewModel> subforoViewModel = new SubforoAssembler().ConvertListENToModel(subforosEN).ToList();
            SessionClose();

            return View(subforoViewModel);
        }

        public ActionResult Indice()
        {
            SessionInitialize();
            SubforoCAD subforoCAD = new SubforoCAD(session);
            SubforoCEN subforoCEN = new SubforoCEN(subforoCAD);

            IList<SubforoEN> subforosEN = subforoCEN.ReadAll(0, -1);
            IEnumerable<SubforoViewModel> subforoViewModel = new SubforoAssembler().ConvertListENToModel(subforosEN).ToList();
            SessionClose();

            return View(subforoViewModel);
        }

        public ActionResult Dados()
        {

            return View();
        }

        // GET: Subforo/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();
            SubforoCAD subforoCAD = new SubforoCAD(session);
            SubforoCEN subforoCEN = new SubforoCEN(subforoCAD);

            SubforoEN subforoEN = subforoCEN.ReadOID(id);
            SubforoViewModel subforoViewModel = new SubforoAssembler().ConvertENToModelUI(subforoEN);
            SessionClose();

            return View(subforoViewModel);
        }

        public ActionResult Detalles(int id)
        {
            SessionInitialize();
            SubforoCAD subforoCAD = new SubforoCAD(session);
            SubforoCEN subforoCEN = new SubforoCEN(subforoCAD);

            SubforoEN subforoEN = subforoCEN.ReadOID(id);
            SubforoViewModel subforoViewModel = new SubforoAssembler().ConvertENToModelUI(subforoEN);
            SessionClose();

            return View(subforoViewModel);
        }

        // GET: Subforo/Create
        [Authorize]
        public ActionResult Create()
        {
            return View();
        }

        // POST: Subforo/Create
        [HttpPost]
        public ActionResult Create(SubforoViewModel sforo)
        {
            try
            {
                // TODO: Add insert logic here
                SubforoCEN subforoCEN = new SubforoCEN();
                if (Session["Usuario"] != null)
                {
                    sforo.Autor = ((UsuarioEN)Session["Usuario"]).Nickname;
                    subforoCEN.New_(((UsuarioEN)Session["Usuario"]).Id, sforo.Titulo, DateTime.Now, sforo.Descripcion, 0);
                }

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
        [Authorize]
        public ActionResult Crear()
        {
            return View();
        }

        // POST: Subforo/Create
        [HttpPost]
        public ActionResult Crear(SubforoViewModel sforo)
        {
            try
            {
                // TODO: Add insert logic here
                SubforoCEN subforoCEN = new SubforoCEN();
                if (Session["Usuario"] != null)
                {
                    sforo.Autor = ((UsuarioEN)Session["Usuario"]).Nickname;
                    subforoCEN.New_(((UsuarioEN)Session["Usuario"]).Id, sforo.Titulo, DateTime.Now, sforo.Descripcion, 0);
                }

                return RedirectToAction("Indice");
            }
            catch
            {
                return View();
            }
        }

        // GET: Subforo/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            SubforoCAD subforoCAD = new SubforoCAD(session);
            SubforoCEN subforoCEN = new SubforoCEN(subforoCAD);

            SubforoEN subforoEN = subforoCEN.ReadOID(id);
            SubforoViewModel subforoViewModel = new SubforoAssembler().ConvertENToModelUI(subforoEN);

            SessionClose();

            return View(subforoViewModel);
        }

        // POST: Subforo/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, SubforoViewModel sforo)
        {
            try
            {
                // TODO: Add update logic here
                SubforoCEN subforoCEN = new SubforoCEN();
                SubforoEN subforoEN = subforoCEN.ReadOID(id);
                subforoCEN.Modify(id, sforo.Titulo, DateTime.Now, sforo.Descripcion, subforoEN.NumEntradas);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Subforo/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            SubforoCAD subforoCAD = new SubforoCAD(session);
            SubforoCEN subforoCEN = new SubforoCEN(subforoCAD);

            SubforoEN subforoEN = subforoCEN.ReadOID(id);
            SubforoViewModel subforoViewModel = new SubforoAssembler().ConvertENToModelUI(subforoEN);
            SessionClose();

            return View(subforoViewModel);
        }

        // POST: Subforo/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, SubforoViewModel sforo)
        {
            try
            {
                // TODO: Add delete logic here
                SubforoCEN subforoCEN = new SubforoCEN();
                EntradaCEN entradaCEN = new EntradaCEN();
                UsuarioCEN usuarioCEN = new UsuarioCEN();
                EntradaCP entradaCP = new EntradaCP();
                IList<EntradaEN> comentarios = entradaCEN.GetEntradasSubforo(id);
                foreach(EntradaEN en in comentarios)
                {
                    entradaCP.Destroy(en.Id);
                }

                //UNRELATIONER DE USUARIOS

                IList<int> idUsuario = new List<int>();
                IList<UsuarioEN> seguidores = subforoCEN.GetUsuariosSubforo(id);
                foreach (UsuarioEN usu in seguidores)
                {
                    idUsuario.Add(usu.Id);
                }
                subforoCEN.DejarSeguirSubforo(id, idUsuario);

                subforoCEN.Destroy(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        public ActionResult Comentarios(int id)
        {
            SessionInitialize();
            EntradaCAD entradaCAD = new EntradaCAD(session);
            EntradaCEN entradaCEN = new EntradaCEN(entradaCAD);

            IList<EntradaEN> entradasEN = entradaCEN.GetEntradasSubforo(id);
            IEnumerable<EntradaViewModel> entradasViewModel = new EntradaAssembler().ConvertListENToModel(entradasEN).ToList();
            SessionClose();

            return PartialView(entradasViewModel);
        }
        [Authorize]
        public ActionResult Comentar()
        {
            return PartialView();
        }
        [HttpPost]
        public ActionResult Comentar(int id, EntradaViewModel comentario)
        {
            try
            {
                // TODO: Add insert logic here
                EntradaCP entradaCP = new EntradaCP();
                if (Session["Usuario"] != null)
                {
                    comentario.Usuario = ((UsuarioEN)Session["Usuario"]).Nickname;
                    comentario.idUsuario = ((UsuarioEN)Session["Usuario"]).Id;
                    comentario.idSubforo = id;
                    entradaCP.New_(comentario.idSubforo, comentario.idUsuario, comentario.Texto);
                }

                return PartialView();
            }
            catch
            {
                return PartialView();
            }
        }
        [Authorize]
        public ActionResult Seguir()
        {
            return PartialView();
        }
        [HttpPost]
        public ActionResult Seguir(int id, SubforoViewModel sforo)
        {
            try
            {
                // TODO: Add insert logic here
                SubforoCEN subforoCEN = new SubforoCEN();
                IList<int> us = new List<int>();
                if (Session["Usuario"] != null)
                {
                    us.Add(((UsuarioEN)Session["Usuario"]).Id);
                    IList<UsuarioEN> seguidores = subforoCEN.GetUsuariosSubforo(id);
                    foreach (UsuarioEN usu in seguidores)
                    {
                        if (usu.Id == us[0])
                        {
                            return PartialView();
                        }
                    }

                    subforoCEN.SeguirSubforo(id, us);
                }

                return PartialView();
            }
            catch
            {
                return PartialView();
            }
        }
        [Authorize]
        public ActionResult DejarSeguir()
        {
            return PartialView();
        }
        [HttpPost]
        public ActionResult DejarSeguir(int id, SubforoViewModel sforo)
        {
            try
            {
                // TODO: Add insert logic here
                SubforoCEN subforoCEN = new SubforoCEN();
                IList<int> us = new List<int>();
                if (Session["Usuario"] != null)
                {
                    us.Add(((UsuarioEN)Session["Usuario"]).Id);
                    IList<UsuarioEN> seguidores = subforoCEN.GetUsuariosSubforo(id);
                    foreach (UsuarioEN usu in seguidores)
                    {
                        if (usu.Id == us[0])
                        {
                            subforoCEN.DejarSeguirSubforo(id, us);
                            return PartialView();
                        }
                    }
                }

                return PartialView();
            }
            catch
            {
                return PartialView();
            }
        }

        public ActionResult Seguidos()
        {
            SessionInitialize();
            SubforoCAD subforoCAD = new SubforoCAD(session);
            SubforoCEN subforoCEN = new SubforoCEN(subforoCAD);

            IList<SubforoEN> subforosEN = subforoCEN.GetSeguidosUsuario((int) Session["Usu_id"]);
            IEnumerable<SubforoViewModel> subforoViewModel = new SubforoAssembler().ConvertListENToModel(subforosEN).ToList();
            SessionClose();

            return View(subforoViewModel);
        }
    }
}
