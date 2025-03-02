import {Component, OnInit} from '@angular/core';
import {ActivatedRoute, Router} from "@angular/router";
import {ApiService} from "../../../servicios/api/api.service";
import {FormBuilder, FormControl, FormGroup, Validators} from "@angular/forms";
import {CitaInterface} from "../../../modelos/cita.interface";
import {defaultMedico, MedicoInterface} from "../../../modelos/medico.interface";
import {defaultPaciente, PacienteInterface} from "../../../modelos/paciente.interface";
import { DiagnosticoInterface } from "../../../modelos/diagnostico.interface";
import { DatePipe } from '@angular/common';

@Component({
  selector: 'app-editar-cita',
  templateUrl: './editar-cita.component.html',
  styleUrls: ['./editar-cita.component.css'],
  providers: [DatePipe]
})
export class EditarCitaComponent implements  OnInit {

  campos = true;
  wrongDateFormat = false;
  medicos:MedicoInterface[] = [];
  pacientes:PacienteInterface[] = [];
  originalMed:MedicoInterface = new defaultMedico();
  originalPac:PacienteInterface = new defaultPaciente();
  constructor(private activeroute: ActivatedRoute, private router: Router, private api: ApiService, private fb: FormBuilder, private datePipe: DatePipe) {

    this.api.getAllMedicos().subscribe(data =>{
      this.medicos = data;
    });
    this.api.getAllPacientes().subscribe(data =>{
      this.pacientes = data;
    });
    this.fullForm = this.fb.group(this.editarForm, this.diagnosticoForm);
  }
  editarForm = new FormGroup({
    id: new FormControl<number>(0, { nonNullable: true}),
    fechaHora: new FormControl<string>("", { nonNullable: true, validators: [Validators.required ]}),
    motivoCita: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    medico: new FormControl<MedicoInterface>(new defaultMedico(), { nonNullable: true, validators: [Validators.required] }),
    paciente: new FormControl<PacienteInterface>(new defaultPaciente(), { nonNullable: true, validators: [Validators.required] })
  });

  diagnosticoForm= new FormGroup({
    id: new FormControl<number>(0, { nonNullable: true, validators: [Validators.required] }),
    enfermedad: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    valoracion: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] })
  });
  fullForm: FormGroup;



  ngOnInit(): void {
    let citaId = this.activeroute.snapshot.paramMap.get('id');
    if(citaId!=null){
      this.api.getCita(citaId).subscribe(data=>{
        let datosCita = data;
        let dateData = this.datePipe.transform(datosCita.fechaHora!, 'yyyy-MM-dd HH:mm:ss')!;
        this.editarForm.setValue({
          id: Number(citaId)!,
          fechaHora: dateData,
          motivoCita: datosCita.motivoCita!,
          medico: datosCita.medico!,
          paciente: datosCita.paciente!
        });
        this.diagnosticoForm.setValue({
          id: Number(datosCita.diagnostico!.id)!,
          enfermedad: datosCita.diagnostico!.enfermedad!,
          valoracion: datosCita.diagnostico!.valoracion!
        });
        console.log(this.editarForm.value);
        this.originalMed=datosCita.medico!;
        this.originalPac=datosCita.paciente!;
      });
    }
  }

  //comprobacion de los campos antes de hacer peticion
  lecturaCampos() {
    if (this.editarForm.controls.fechaHora.errors?.['required'] ||
      this.editarForm.controls.motivoCita.errors?.['required'] ||
      this.editarForm.controls.medico.errors?.['required'] ||
      this.editarForm.controls.paciente.errors?.['required'] ||
      this.diagnosticoForm.controls.enfermedad.errors?.['required'] ||
      this.diagnosticoForm.controls.valoracion.errors?.['required']
      
    ) {
      this.campos = false;
    }
    else {
      this.campos = true;
    }

  }

  postForm(form:CitaInterface, form2: DiagnosticoInterface){
    try {
      let dateData = this.datePipe.transform(form.fechaHora!, 'yyyy-MM-dd HH:mm:ss')!;

      this.lecturaCampos();
      if (this.campos) {
        this.api.putDiagnostico(form2).subscribe(data => {
          this.api.getDiagnostico(data.id!.toString()).subscribe(data2 => {
            form.diagnostico = data2;
            this.api.putCita(form).subscribe(data3 => {
              console.log(data3);
              this.router.navigate(['cita']);
            })
          })
        })
      }
      
      

    }
    catch (e: any) {
      this.wrongDateFormat = true;
      console.log(e);

    }
    


  }


  atras() {
    this.router.navigate(['verCita', this.editarForm.value.id!]);
  }



}
