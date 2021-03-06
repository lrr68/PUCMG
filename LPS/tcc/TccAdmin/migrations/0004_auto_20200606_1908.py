# Generated by Django 3.0.5 on 2020-06-06 19:08

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('TccAdmin', '0003_auto_20200503_1148'),
    ]

    operations = [
        migrations.CreateModel(
            name='Horario',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('horario', models.DateTimeField()),
                ('preenchido', models.BooleanField(default=False)),
            ],
        ),
        migrations.RemoveField(
            model_name='banca',
            name='horario',
        ),
        migrations.RemoveField(
            model_name='grade',
            name='h1',
        ),
        migrations.RemoveField(
            model_name='grade',
            name='h2',
        ),
        migrations.RemoveField(
            model_name='grade',
            name='h3',
        ),
        migrations.RemoveField(
            model_name='grade',
            name='h4',
        ),
        migrations.RemoveField(
            model_name='grade',
            name='h5',
        ),
        migrations.RemoveField(
            model_name='grade',
            name='h6',
        ),
        migrations.AlterField(
            model_name='banca',
            name='professor',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='TccAdmin.Professor'),
        ),
        migrations.AddField(
            model_name='grade',
            name='horarios',
            field=models.ManyToManyField(to='TccAdmin.Horario'),
        ),
    ]
