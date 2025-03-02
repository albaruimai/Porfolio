import {MedicoInterface} from "./medico.interface";

export interface PacienteInterface{
    id?:number;
    usuario?:string;
    nombre?:string;
    apellidos?:string;
    clave?:string;
    nss?:string;
    numTarjeta?:string;
    telefono?:string;
    direccion?:string;
}

export class defaultPaciente implements PacienteInterface{
  id: number = 0;
  usuario:string= '';
  nombre:string= '';
  apellidos:string= '';
  clave:string= '';
  nss:string= '';
  numTarjeta:string= '';
  telefono:string= '';
  direccion:string= '';


}

