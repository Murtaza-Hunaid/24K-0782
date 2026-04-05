from pgmpy.models import DiscreteBayesianNetwork as BayesianNetwork
from pgmpy.factors.discrete import TabularCPD
from pgmpy.inference import VariableElimination

model = BayesianNetwork([
    ('Intelligence', 'Grade'),
    ('StudyHours', 'Grade'),
    ('Difficulty', 'Grade'),
    ('Grade', 'Pass')
])

cpd_I = TabularCPD('Intelligence', 2, [[0.7], [0.3]], state_names={'Intelligence': ['High', 'Low']})
cpd_S = TabularCPD('StudyHours', 2, [[0.6], [0.4]], state_names={'StudyHours': ['Sufficient', 'Insufficient']})
cpd_D = TabularCPD('Difficulty', 2, [[0.4], [0.6]], state_names={'Difficulty': ['Hard', 'Easy']})

grade_table = [
    [0.50, 0.85, 0.30, 0.65, 0.20, 0.55, 0.05, 0.25],  # A
    [0.35, 0.12, 0.45, 0.28, 0.45, 0.35, 0.30, 0.45],  # B
    [0.15, 0.03, 0.25, 0.07, 0.35, 0.10, 0.65, 0.30],  # C
]

cpd_G = TabularCPD('Grade', 3, grade_table, evidence=['Intelligence', 'StudyHours', 'Difficulty'], evidence_card=[2, 2, 2],
    state_names={
        'Grade':        ['A', 'B', 'C'],
        'Intelligence': ['High', 'Low'],
        'StudyHours':   ['Sufficient', 'Insufficient'],
        'Difficulty':   ['Hard', 'Easy'], }
)

cpd_P = TabularCPD('Pass', 2, [[0.95, 0.80, 0.50], [0.05, 0.20, 0.50]], evidence=['Grade'], evidence_card=[3],
    state_names={
        'Pass':  ['Yes', 'No'],
        'Grade': ['A', 'B', 'C'], }
)

model.add_cpds(cpd_I, cpd_S, cpd_D, cpd_G, cpd_P)
assert model.check_model(), "Model is invalid!"

ve = VariableElimination(model)

q1 = ve.query(variables=['Pass'], evidence={'StudyHours': 'Sufficient', 'Difficulty': 'Hard'})
print("4.1: P(Pass | StudyHours=Sufficient, Difficulty=Hard):-")
print(q1)

q2 = ve.query(variables=['Intelligence'], evidence={'Pass': 'Yes'})
print("\n4.2: P(Intelligence | Pass=Yes):-")
print(q2)
q1_yes  = float(q1.values[list(q1.state_names['Pass']).index('Yes')])
q2_high = float(q2.values[list(q2.state_names['Intelligence']).index('High')])
print(f"\nP(Pass=Yes | StudyHours=Sufficient, Difficulty=Hard) = {q1_yes:.4f} ({q1_yes*100:.2f}%)")
print(f"P(I=High | Pass=Yes) = {q2_high:.4f} ({q2_high*100:.2f}%)")
