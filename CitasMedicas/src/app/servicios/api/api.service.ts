import { Injectable } from '@angular/core';
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {ResponseI, Credentials} from "../../modelos/response.interface";
import {Observable} from "rxjs";
import { map } from 'rxjs/operators';
import {PacienteInterface} from "../../modelos/paciente.interface";
import {MedicoInterface} from "../../modelos/medico.interface";
import {CitaInterface} from "../../modelos/cita.interface";
import {DiagnosticoInterface} from "../../modelos/diagnostico.interface";
import { JwtHelperService } from '@auth0/angular-jwt';

@Injectable({
  providedIn: 'root'
})
export class ApiService {
  HttpOptions = {
    headers: new HttpHeaders()
  }

  constructor(private http: HttpClient) {}

  //Modificar luego para poder paginar esto


  //PACIENTES
  getAllPacientes():Observable<PacienteInterface[]>{
    return this.http.get<PacienteInterface[]>('http://localhost:8080/api/paciente/all', this.HttpOptions);
  }

  getPaciente(id:string):Observable<PacienteInterface>{
    return this.http.get<PacienteInterface>('http://localhost:8080/api/paciente/all/' +id, this.HttpOptions);
  }

  putPaciente(form:PacienteInterface):Observable<ResponseI>{
    return this.http.put<ResponseI>('http://localhost:8080/api/paciente/all/' + form.id, form, this.HttpOptions);
  }

  deletePaciente(form:PacienteInterface):Observable<ResponseI>{
    return this.http.delete<ResponseI>('http://localhost:8080/api/paciente/all/' + form.id, this.HttpOptions);
  }
  postPaciente(form:PacienteInterface):Observable<ResponseI>{
    return this.http.post<ResponseI>('http://localhost:8080/api/paciente/all', form, this.HttpOptions);
  }

  getMisMedicos(id:string):Observable<MedicoInterface[]>{
    return this.http.get<MedicoInterface[]>('http://localhost:8080/api/paciente/all/'+id+'/medicos', this.HttpOptions);
  }


  //MEDICOS
  getAllMedicos():Observable<MedicoInterface[]>{
    return this.http.get<MedicoInterface[]>('http://localhost:8080/api/medico/all', this.HttpOptions);
  }

  getMedico(id:string):Observable<MedicoInterface>{
    return this.http.get<MedicoInterface>('http://localhost:8080/api/medico/all/' +id, this.HttpOptions);
  }

  putMedico(form:MedicoInterface):Observable<ResponseI>{
    return this.http.put<ResponseI>('http://localhost:8080/api/medico/all/' + form.id, form, this.HttpOptions);
  }

  deleteMedico(form:MedicoInterface):Observable<ResponseI>{
    return this.http.delete<ResponseI>('http://localhost:8080/api/medico/all/' + form.id, this.HttpOptions);
  }

  postMedico(form:MedicoInterface):Observable<ResponseI>{
    return this.http.post<ResponseI>('http://localhost:8080/api/medico/all', form, this.HttpOptions);
  }

  getMisPacientes(id:string):Observable<PacienteInterface[]>{
  return this.http.get<PacienteInterface[]>('http://localhost:8080/api/medico/all/'+id+'/pacientes', this.HttpOptions);
  }

  //CITAS

  getAllCitas():Observable<CitaInterface[]>{
    return this.http.get<CitaInterface[]>('http://localhost:8080/api/cita/all', this.HttpOptions);
  }
  getCita(id:string):Observable<CitaInterface>{
    return this.http.get<CitaInterface>('http://localhost:8080/api/cita/all/' +id, this.HttpOptions);
  }

  putCita(form:CitaInterface):Observable<ResponseI>{
    return this.http.put<ResponseI>('http://localhost:8080/api/cita/all/' + form.id, form, this.HttpOptions);
  }


  deleteCita(form: CitaInterface): Observable<ResponseI> {
    return this.http.delete<ResponseI>('http://localhost:8080/api/cita/all/' + form.id, this.HttpOptions);
  }

  postCita(form:CitaInterface):Observable<ResponseI>{
    return this.http.post<ResponseI>('http://localhost:8080/api/cita/all', form, this.HttpOptions);
  }


  //DIAGNOSTICOS

  getAllDiagnosticos():Observable<DiagnosticoInterface[]>{
    return this.http.get<DiagnosticoInterface[]>('http://localhost:8080/api/diagnostico/all', this.HttpOptions);
  }

  getDiagnostico(id:string):Observable<DiagnosticoInterface>{
    return this.http.get<DiagnosticoInterface>('http://localhost:8080/api/diagnostico/all/' +id, this.HttpOptions);
  }


  putDiagnostico(form:DiagnosticoInterface):Observable<ResponseI>{
    return this.http.put<ResponseI>('http://localhost:8080/api/diagnostico/all/' + form.id, form, this.HttpOptions);
  }

  deleteDiagnostico(form: DiagnosticoInterface): Observable<ResponseI> {
    return this.http.delete<ResponseI>('http://localhost:8080/api/diagnostico/all/' + form.id, this.HttpOptions);
  }

  postDiagnostico(form:DiagnosticoInterface):Observable<ResponseI>{
    return this.http.post<ResponseI>('http://localhost:8080/api/diagnostico/all', form, this.HttpOptions);
  }


//LOGIN

  login(creds: Credentials){
    return this.http.post('http://localhost:8080/login', creds, {
      observe: 'response'
    }).pipe(map(response =>{
        const body = response.body;
        const headers = response.headers;

        const bearerToken = headers.get('Authorization')!;
        const token = bearerToken.replace('Bearer ', '');
        localStorage.setItem('token', token);
        return body;

      }

    ))
  }

  getToken(){
    return localStorage.getItem('token');
  }

  getTipoToken(): any {
    const helper = new JwtHelperService();
      try {
        const decodedToken = helper.decodeToken(localStorage.getItem('token')!);
        return decodedToken ? decodedToken['tipo'] : null;
      } catch(Error) {
        return null;
    }
  }


  getIdToken(): any {
    const helper = new JwtHelperService();
    try {
      const decodedToken = helper.decodeToken(localStorage.getItem('token')!);
      return decodedToken ? decodedToken['id'] : null;
    } catch(Error) {
      return null;
    }
  }

  getDecodedToken():any{
    const helper = new JwtHelperService();
    return helper.decodeToken(localStorage.getItem('token')!);
  }

  deleteToken(){
    localStorage.removeItem('token');
  }


}
