export interface MedicoInterface{
  id?:number;
  usuario?:string;
  nombre?:string;
  apellidos?:string;
  clave?:string;
  numColegiado?:string;
}

export class defaultMedico implements MedicoInterface{
  id: number = 0;
  usuario:string= '';
  nombre:string= '';
  apellidos:string= '';
  clave:string= '';
  numColegiado:string= '';
}



