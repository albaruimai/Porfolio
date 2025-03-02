import { Component , OnInit} from '@angular/core';
import {Router, ActivatedRoute} from "@angular/router";
import {ApiService} from "../../../servicios/api/api.service";
import {PacienteInterface} from "../../../modelos/paciente.interface";
import {FormGroup, FormControl, Validators} from "@angular/forms";

@Component({
  selector: 'app-editar-paciente',
  templateUrl: './editar-paciente.component.html',
  styleUrls: ['./editar-paciente.component.css']
})
export class EditarPacienteComponent implements OnInit{

  constructor(private activeroute:ActivatedRoute, private router:Router, private api:ApiService) {

  }
  campos = true;
  telefono = true;

  editarForm = new FormGroup({
    id: new FormControl<number>(0, { nonNullable: true, validators: [Validators.required] }),
    usuario: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    nombre: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    apellidos: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    clave: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    numTarjeta: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    nss: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    telefono: new FormControl<string>('', { nonNullable: true, validators: [Validators.required, Validators.pattern("[0-9 ]{9}")] }),
    direccion: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] })
  });

  ngOnInit(): void {
    let pacienteId = this.activeroute.snapshot.paramMap.get('id');
    if(pacienteId!=null){
      this.api.getPaciente(pacienteId).subscribe(data=>{
        let datosPaciente = data;
        this.editarForm.setValue({
          id: Number(pacienteId)!,
          usuario: datosPaciente.usuario!,
          nombre: datosPaciente.nombre!,
          apellidos: datosPaciente.apellidos!,
          clave: datosPaciente.clave!,
          numTarjeta: datosPaciente.numTarjeta!,
          nss: datosPaciente.nss!,
          telefono: datosPaciente.telefono!,
          direccion: datosPaciente.direccion!
      });
        console.log(this.editarForm.value);
      });

    }
  }

  //comprobacion de los campos antes de hacer peticion
  lecturaCampos() {
    if (this.editarForm.controls.usuario.errors?.['required'] ||
      this.editarForm.controls.nombre.errors?.['required'] ||
      this.editarForm.controls.apellidos.errors?.['required'] ||
      this.editarForm.controls.clave.errors?.['required'] ||
      this.editarForm.controls.numTarjeta.errors?.['required'] ||
      this.editarForm.controls.nss.errors?.['required'] ||
      this.editarForm.controls.telefono.errors?.['required'] ||
      this.editarForm.controls.direccion.errors?.['required']

    ){
      this.campos = false;
      
    }
    else {
      this.campos = true;
    }
    if (this.editarForm.controls.telefono.errors?.['pattern']) {
      this.telefono = false;
    } else {
        this.telefono = true;
    }
  }


  postForm(form: PacienteInterface) {
    this.lecturaCampos()
    if (this.campos && this.telefono) {
      this.api.putPaciente(form).subscribe(data=>{
        console.log(data);
        this.router.navigate(['paciente']);
      })
    }
    
  }

  atras(){
    this.router.navigate(['verPaciente', this.editarForm.value.id!]);
  }

}
