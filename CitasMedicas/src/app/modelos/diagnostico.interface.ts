
export interface DiagnosticoInterface{
  id?:number;
  valoracion?:string;
  enfermedad?:string;
}
export class defaultDiagnostico implements DiagnosticoInterface{
  id: number=0;
  valoracion: string = '';
  enfermedad: string = '';
}
