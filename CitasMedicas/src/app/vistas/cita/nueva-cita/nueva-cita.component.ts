import {Component, Input, OnInit} from '@angular/core';
import {ActivatedRoute, Router} from "@angular/router";
import {ApiService} from "../../../servicios/api/api.service";
import {FormBuilder, FormControl, FormGroup, Validators} from "@angular/forms";
import {CitaInterface} from "../../../modelos/cita.interface";
import {defaultMedico, MedicoInterface} from "../../../modelos/medico.interface";
import {defaultPaciente, PacienteInterface} from "../../../modelos/paciente.interface";
import {DiagnosticoInterface } from "../../../modelos/diagnostico.interface";
import { DatePipe } from '@angular/common';

@Component({
  selector: 'app-nueva-cita',
  templateUrl: './nueva-cita.component.html',
  styleUrls: ['./nueva-cita.component.css'],
  providers: [DatePipe]
})

export class NuevaCitaComponent  implements  OnInit {

  campos = true;
  wrongDateFormat = false;
  medicos:MedicoInterface[] = [];
  pacientes:PacienteInterface[] = [];
  constructor(private activeroute: ActivatedRoute, private router: Router, private api: ApiService, private fb: FormBuilder, private datePipe: DatePipe) {

    this.api.getAllMedicos().subscribe(data =>{
      this.medicos = data;
    });
    this.api.getAllPacientes().subscribe(data =>{
      this.pacientes = data;
    });
    this.fullForm = this.fb.group(this.nuevoForm, this.diagnosticoForm);
    this.wrongDateFormat = false;
  }
  nuevoForm = new FormGroup({
    fechaHora: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    motivoCita: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    medico: new FormControl<MedicoInterface>(new defaultMedico(), { nonNullable: true, validators: [Validators.required] }),
    paciente: new FormControl<PacienteInterface>(new defaultPaciente(), { nonNullable: true, validators: [Validators.required] })
  });

  diagnosticoForm= new FormGroup({
    enfermedad: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    valoracion: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] })
});
  fullForm: FormGroup;



  ngOnInit(): void {
  }

  //comprobacion de los campos antes de hacer peticion
  lecturaCampos() {
    if (this.nuevoForm.controls.fechaHora.errors?.['required'] ||
      this.nuevoForm.controls.motivoCita.errors?.['required'] ||
      this.nuevoForm.controls.medico.errors?.['required'] ||
      this.nuevoForm.controls.paciente.errors?.['required'] ||
      this.diagnosticoForm.controls.enfermedad.errors?.['required'] ||
      this.diagnosticoForm.controls.valoracion.errors?.['required']

    ) {
      this.campos = false;
    }
    else {
      this.campos = true;
    }

  }

  postForm(form: CitaInterface, form2: DiagnosticoInterface) {
    try {
      let dateData = this.datePipe.transform(form.fechaHora!, 'yyyy-MM-dd HH:mm:ss')!;
      this.lecturaCampos();
      if (this.campos) {
        this.api.postDiagnostico(form2).subscribe(data => {
          this.api.getDiagnostico(data.id!.toString()).subscribe(data2 => {
            form.diagnostico = data2;
            this.api.postCita(form).subscribe(data3 => {
              console.log(data3);
              this.router.navigate(['cita']);
            })
          });
        });
      }
      


    }
    catch (e: any) {
      this.wrongDateFormat = true;
      console.log(e);

    }
  }

  atras() {
    this.router.navigate(['cita']);
  }



}
