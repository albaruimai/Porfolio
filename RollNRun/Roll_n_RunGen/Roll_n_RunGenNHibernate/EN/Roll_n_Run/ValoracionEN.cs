
using System;
// Definición clase ValoracionEN
namespace Roll_n_RunGenNHibernate.EN.Roll_n_Run
{
public partial class ValoracionEN
{
/**
 *	Atributo valor
 */
private double valor;



/**
 *	Atributo id
 */
private int id;



/**
 *	Atributo comentario
 */
private string comentario;



/**
 *	Atributo producto
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN producto;



/**
 *	Atributo usuario
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario;






public virtual double Valor {
        get { return valor; } set { valor = value;  }
}



public virtual int Id {
        get { return id; } set { id = value;  }
}



public virtual string Comentario {
        get { return comentario; } set { comentario = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN Producto {
        get { return producto; } set { producto = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN Usuario {
        get { return usuario; } set { usuario = value;  }
}





public ValoracionEN()
{
}



public ValoracionEN(int id, double valor, string comentario, Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN producto, Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario
                    )
{
        this.init (Id, valor, comentario, producto, usuario);
}


public ValoracionEN(ValoracionEN valoracion)
{
        this.init (Id, valoracion.Valor, valoracion.Comentario, valoracion.Producto, valoracion.Usuario);
}

private void init (int id
                   , double valor, string comentario, Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN producto, Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario)
{
        this.Id = id;


        this.Valor = valor;

        this.Comentario = comentario;

        this.Producto = producto;

        this.Usuario = usuario;
}

public override bool Equals (object obj)
{
        if (obj == null)
                return false;
        ValoracionEN t = obj as ValoracionEN;
        if (t == null)
                return false;
        if (Id.Equals (t.Id))
                return true;
        else
                return false;
}

public override int GetHashCode ()
{
        int hash = 13;

        hash += this.Id.GetHashCode ();
        return hash;
}
}
}
